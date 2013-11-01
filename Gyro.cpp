#include "Gyro.h"

Gyro::Gyro() {
  _init = false;
}

void Gyro::init(uint8_t int1, uint8_t int2) {
  init(int1, int2, GYRO_CS);
}

void Gyro::init(uint8_t int1, uint8_t int2, uint8_t cs) {
  init(int1, int2, cs, S250);
}

void Gyro::init(uint8_t int1, uint8_t int2, uint8_t cs, uint8_t bandwidth) {
  _int1 = int1;
  _int2 = int2;
  _cs = cs;
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  pinMode(_int1, INPUT);
  pinMode(_int2, INPUT);
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, HIGH);

  // The WHO_AM_I register should identify 0xD3
  if(read_register(WHO_AM_I)!=0xD3)
    return;
  
  // Enable x, y, z and turn off power down
  write_register(CTRL_REG1, 0b00011111);
  // Not using any filters
  write_register(CTRL_REG2, 0b00000000);
  //Generate Data Ready Interrupt on INT2
  write_register(CTRL_REG3, 0b00001000);
  // CTRL_REG4 controls the full-scale range, among other things:
  write_register(CTRL_REG4, bandwidth);
  // Not using any filters
  write_register(CTRL_REG5, 0b00000000);
  
  switch(bandwidth) {
    case S250:
      _dps_per_raw = S250DPS;
      break;
    case S500:
      _dps_per_raw = S500DPS;
      break;
    case S2000:
      _dps_per_raw = S2000DPS;
      break;
  }
  
  delay(100);
  _init = true;
  calibrate();
}

void Gyro::calibrate() {
  if(!_init)
    return;
  
  long int sums[3]={0};
  long int sigma[3]={0};
 
  for (int i=0;i<NUM_SAMPLES;i++) {
    update();
    for (int j=0;j<3;j++) {
      sums[j]+=_raw[j];
      sigma[j]+=_raw[j]*_raw[j];
    }
  }
  
  for (int i=0;i<3;i++) {
    int average_rate=sums[i]/NUM_SAMPLES;
    
    // Per STM docs, take the average of the samples for each axis and subtract them when we use the data.
    _zero[i]=average_rate;
    
    // Per STM docs, a threshold for each axis is based on the standard deviation of the samples times 3.
    _threshold[i]=sqrt((double(sigma[i]) / NUM_SAMPLES) - (average_rate * average_rate)) * SIGMA_MULTIPLE;    
  }
}

void Gyro::update() {
  if(!_init)
    return;
  
  //wait for data, or else may get bad data! Consider rework?
  while (!(read_register(0x27) & B00001000)){};
  if (read_register(0x27) & B01000000)
    _missed_data = true;
  else
    _missed_data = false;
    
  int reg=OUT_X_L; //starting register, x
  for (int i=0; i<3; i++) {
    //OR the H(MSBs) and L(LSBs) of each axis (2 8-bit registers, 1 16-bit number)
    _raw[i]=(read_register(reg) | (read_register(reg+1)<<8));
    reg+=2; //move to next register
  }
  
  int delta[3];
  for (int i=0; i<3; i++)
  {
    delta[i]=_raw[i]-_zero[i];      // Use the calibration data to modify the sensor value.
    if (abs(delta[i]) < _threshold[i])
      delta[i]=0;
    _dps[i]= _dps_per_raw * delta[i];      // Multiply the sensor value by the sensitivity factor to get degrees per second.
  }
}

void Gyro::update_heading() {
  if(!_init)
    return;
  
  float deltaT=get_deltaT_micros();

  for (int i=0; i<3; i++)
    _heading[i] -= (_dps[i]*deltaT)/1000000.0f;
}

int16_t Gyro::get_raw_x() {return _raw[0];}
int16_t Gyro::get_raw_y() {return _raw[1];}
int16_t Gyro::get_raw_z() {return _raw[2];}

int16_t Gyro::get_dps_x() {return _dps[0];}
int16_t Gyro::get_dps_y() {return _dps[1];}
int16_t Gyro::get_dps_z() {return _dps[2];}

float Gyro::get_heading_x() {return _heading[0];}
float Gyro::get_heading_y() {return _heading[1];}
float Gyro::get_heading_z() {return _heading[2];}

uint64_t get_deltaT_micros() {
  static uint64_t last_time=0; //consider making method field?
  
  uint64_t current_time=micros();
  
  uint64_t deltaT=current_time-last_time;
  if (deltaT < 0.0)
     deltaT=current_time+(4294967295-last_time);
   
  last_time=current_time;
  
  return deltaT;
}

int8_t Gyro::read_register(uint8_t address) {
  int to_read;
  
  address |= 0x80;  // This tells the gyro we're reading
  
  digitalWrite(_cs, LOW);
  SPI.transfer(address);
  to_read = SPI.transfer(0x00);
  digitalWrite(_cs, HIGH);
  
  return to_read;
}

void Gyro::write_register(uint8_t address, int8_t data) {
  address &= 0x7F;  // This tells the gyro we're writing
  
  digitalWrite(_cs, LOW);
  SPI.transfer(address);
  SPI.transfer(data);
  digitalWrite(_cs, HIGH);
}


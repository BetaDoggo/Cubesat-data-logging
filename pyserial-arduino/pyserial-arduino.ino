//The code for returning data over the serial monitor.
//Use this with the accompanying python script
//for the sake of readability any sensors that require more than 1 line to read are put into their own functions.
//to do - add remaining sensors
#include "Adafruit_VEML6075.h" //UV library
#include <Adafruit_Sensor.h> //Required for altimeter
#include "Adafruit_BMP3XX.h" //Altimeter library
#include <Wire.h> //Required for I2C, used by UV sensor
#include <SPI.h> //Required to setup altimeter
//////////////temperature variables//////////////
const int lm35_pin1 = A1; //inside temp pin
const int lm35_pin2 = A2; //outside temp pin
int temp_adc_val1; //stores raw temperature reading
float temp_val1; //stores converted temp reading
int temp_adc_val2;
float temp_val2;
////////////////////////////////////////////////
const int MPU = 0x68; //gyro I2C address
//altimeter pins
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10
#define SEALEVELPRESSURE_HPA (1013.25) //used by altimeter for eval
Adafruit_BMP3XX bmp; //Altimeter
//////////////
Adafruit_VEML6075 uv_sensor = Adafruit_VEML6075(); //UV
int i = 0; //Message count - used to measure loss - not trust worthy, time travel has been observed
//sensor data variables - could be an array but this is easier for now
float MessageNum;
float timestamp;
float altitude; //from altimeter
float Extemp;
float Inttemp;
float pressure; //from altimeter
float Xaccel;	
float Yaccel;
float Zaccel;
float XGyro;
float YGyro;
float ZGyro;
float uv;
//string versions for use with sprintf - 10 is probably more than enough, adjust for memory budget
char Stimestamp[10];
char SMessageNum[10];
char Saltitude[10];
char SExtemp[10];
char SInttemp[10];
char Spressure[10];
char SXaccel[10];
char SYaccel[10];
char SZaccel[10];
char SXGyro[10];
char SYGyro[10];
char SZGyro[10];
char Suv[10]; //vroom vroom

char buffer[200]; //buffer to transport buffer data - oversized for testing, resize later

void readTemp(){ //temperature reading function
  temp_adc_val1 = analogRead(lm35_pin1); //get internal temp pin output
  temp_adc_val2 = analogRead(lm35_pin2); //get external temp pin output
  temp_val1 = (temp_adc_val1 * 4.88);
  temp_val2 = (temp_adc_val2 * 4.88);
  Inttemp = (temp_val1/10);
  Extemp = (temp_val2/10);
}

void floatFix() { //sprintf can't handle floats so we need strings instead
  dtostrf(timestamp, 1, 2, Stimestamp); //first number is minimum length, second is digits after decimal
  dtostrf(MessageNum, 1, 2, SMessageNum);
  dtostrf(altitude, 1, 2, Saltitude);
  dtostrf(Extemp, 1, 2, SExtemp);
  dtostrf(Inttemp, 1, 2, SInttemp);
  dtostrf(pressure, 1, 2, Spressure);
  dtostrf(Xaccel, 1, 2, SXaccel);
  dtostrf(Yaccel, 1, 2, SYaccel);
  dtostrf(Zaccel, 1, 2, SZaccel);
  dtostrf(XGyro, 1, 2, SXGyro);
  dtostrf(YGyro, 1, 2, SYGyro);
  dtostrf(ZGyro, 1, 2, SZGyro);
  dtostrf(uv, 1, 2, Suv);
}

void readAltimeter(){ //altimeter reading function
  bmp.performReading();
  pressure = (bmp.pressure / 100.0);
  altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
}

void readMPU(){ //reads the gyro/accel
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true); //stall point 
  Xaccel=Wire.read()<<8|Wire.read();    
  Yaccel=Wire.read()<<8|Wire.read();  
  Zaccel=Wire.read()<<8|Wire.read();  
  XGyro=Wire.read()<<8|Wire.read();  
  YGyro=Wire.read()<<8|Wire.read();  
  ZGyro=Wire.read()<<8|Wire.read(); 
}


void clearSensors(){ //clears sensor variables
  timestamp = 0; //not implemented yet
  altitude = 0;
  Extemp = 0;
  Inttemp = 0;
  pressure = 0;
  Xaccel = 0;	
  Yaccel = 0;
  Zaccel = 0;
  XGyro = 0;
  YGyro = 0;
  ZGyro = 0;
  uv = 0;
}

void setup() {
  Serial.begin(115200);//kind of high, can change later
  uv_sensor.begin(); //init UV serial connection
  //bmp filter init
  bmp.begin_I2C(); //init altimeter in software I2C mode
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
  //gyroscope
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  
  Wire.write(0);    
  Wire.endTransmission(true);
}

void loop() {
  MessageNum = i;
  clearSensors(); //empty the sensor variables to prevent duplicate values
  readMPU();
  readAltimeter();
  //uv = uv_sensor.readUVI(); //function from library
  readTemp(); //will be removed once altimeter is finalized
  //--------------Data collection code goes above----------
  floatFix(); //must be run to convert float variables to strings
  sprintf(buffer, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", SMessageNum,Stimestamp,Saltitude,SExtemp,SInttemp,Spressure,SXaccel,SYaccel,SZaccel,SXGyro,SYGyro,SZGyro,Suv);
  Serial.println(buffer);
  delay(1000); //1s for testing - can go lower but must match the python logging script
  i++;
}
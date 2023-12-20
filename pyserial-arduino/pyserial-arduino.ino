//code used to output data in csv format
//WIP: add code to output to data board - might be able to use the unmodified buffer, can't test yet
//Use the rtc on the databoard for the timestamp
//////////////temperature variables//////////////
const int lm35_pin1 = A1; //inside temp pin
const int lm35_pin2 = A2; //outside temp pin
int temp_adc_val1; //stores raw temperature reading
float temp_val1; //stores converted temp reading
int temp_adc_val2;
float temp_val2;
////////////////////////////////////////////////
int i = 0; //Message count - used to measure loss - not trust worthy, time travel has been observed
//sensor data variables - could be an array but this is easier for now
float MessageNum;
float timestamp;
float altitude;
float Extemp;
float Inttemp;
float pressure;
float Xaccel;	
float Yaccel;
float Zaccel;
float radiation;
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
char Sradiation[10];
char Suv[10]; //vroom vroom

char buffer[120]; //buffer to transport buffer data - oversized for testing, resize later

void readTemp(){ //temperature reading function
  temp_adc_val1 = analogRead(lm35_pin1); //get internal temp pin output
  temp_adc_val2 = analogRead(lm35_pin2); //get external temp pin output
  //temp_adc_val1 = 1; //testing values
  //temp_adc_val2 = 2;
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
  dtostrf(radiation, 1, 2, Sradiation);
  dtostrf(uv, 1, 2, Suv);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  //random values for testing
  MessageNum = i;
  timestamp = 0; //not implemented yet
  altitude = 0;
  Extemp = 0;
  Inttemp = 0;
  pressure = 0;
  Xaccel = 0;	
  Yaccel = 0;
  Zaccel = 0;
  radiation = 0;
  uv = 0;
  readTemp();
  //--------------Data collection code goes above----------
  floatFix(); //must be run to convert float variables to strings
  sprintf(buffer, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", SMessageNum,Stimestamp,Saltitude,SExtemp,SInttemp,Spressure,SXaccel,SYaccel,SZaccel,Sradiation,Suv);
  Serial.println(buffer);
  delay(1000); //1s for testing - can go lower but must match the python logging script
  i = i + 1;
}
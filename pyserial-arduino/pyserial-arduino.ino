//Basic example code showing the format for returning data
//to do: refactor with sprintf

int i = 0; //very basic timestamp for now
//sensor data variables - could be an array but this is easier for now
float timestamp;
float altitude;
float barometer;
float temp;
float pressure;
float Xaccel;	
float Yaccel;
float Zaccel;
float radiation;
float uv;
//string versions for use with sprintf - 10 is probably more than enough, adjust for memory budget
char Stimestamp[10];
char Saltitude[10];
char Sbarometer[10];
char Stemp[10];
char Spressure[10];
char SXaccel[10];
char SYaccel[10];
char SZaccel[10];
char Sradiation[10];
char Suv[10]; //vroom vroom

char buffer[1000]; //too big buffer to hold the sprintf data, uses 50% of ram lol

void floatFix() { //sprintf can't handle floats so we need strings instead
  dtostrf(timestamp, 1, 2, Stimestamp); //first number is minimum length, second is digits after decimal
  dtostrf(altitude, 1, 2, Saltitude);
  dtostrf(barometer, 1, 2, Sbarometer);
  dtostrf(temp, 1, 2, Stemp);
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
  timestamp = i;
  altitude = random(5);
  barometer = random(5);
  temp = random(5);
  pressure = random(5);
  Xaccel = random(5);	
  Yaccel = random(5);
  Zaccel = random(5);
  radiation = random(5);
  uv = random(5);
  //--------------Data collection code goes above----------
  floatFix(); //must be run to convert float variables to strings
  sprintf(buffer, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", Stimestamp,Saltitude,Sbarometer,Stemp,Spressure,SXaccel,SYaccel,SZaccel,Sradiation,Suv);
  Serial.println(buffer);
  delay(1000); //for testing - can go lower but must match the python logging script
  i = i + 1;
}


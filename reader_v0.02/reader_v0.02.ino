
#include <SoftwareSerial.h>
SoftwareSerial gpsSerial(10, 11); //rx,tx

#include "TinyGPS++.h"
TinyGPSPlus gps;


int voltagePin = A1;
int sensorPins[4] = { A2, A3, A4, A5 };
int numberOfSensors = sizeof(sensorPins) / sizeof(sensorPins[0]);




void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
}


float reading = 120.0f;
float getSensorVoltage(int pinNumber) {
  //TODO: apply voltage divider formula to output a result in ohms

  // float vout = readAnalog(pinNumber);
  // float r2 = ...
  // return r2;

   return reading;
}

void combineReadings(float referenceVoltage, float* sensorReadings, char* strResult) {
  strcpy(strResult, "RDG ");
  
  char strVoltage[5];
  dtostrf(referenceVoltage, 5, 2, strVoltage);
  strcat(strResult, strVoltage);
  
  for(int i=0; i<numberOfSensors; ++i) {
    dtostrf(sensorReadings[i], 6, 1, strVoltage);
    strcat(strResult, strVoltage);
  }
}

void readGpsData() {
  while (gpsSerial.available() > 0)
    gps.encode(gpsSerial.read());

  if (gps.location.isUpdated()) {
    Serial.print("GPS ");
    Serial.print(gps.location.lng(), 10); // Longitude in degrees (double)
    Serial.print(" ");
    Serial.print(gps.location.lat(), 10); // Latitude in degrees (double)
    Serial.print(" ");
    Serial.print (gps.speed.kmph() > 3.0 ? gps.speed.kmph() : 0);
    Serial.print(" ");
    Serial.print(gps.course.deg());
    Serial.print(" ");
    Serial.print(gps.satellites.value());
    Serial.print(" ");
    Serial.print(gps.hdop.hdop());
    Serial.println("");
  }
}

void readSensorsData() {
  Serial.print("RDG ");
  Serial.print(getSensorVoltage(voltagePin));
  Serial.print(" ");
  for(int i=0; i<numberOfSensors; ++i) {
    Serial.print(getSensorVoltage(sensorPins[i]));
    Serial.print(" ");
  }
  Serial.print("\n");
}




volatile unsigned long timePointsOpen, timePointsClosed, lastChange;
volatile unsigned int numBangs;

void pointsOpening(){
    unsigned long t;
    t = millis();
    if (lastChange > 0){
        timePointsClosed += (t - lastChange);
    }
    lastChange = t;
    ++numBangs;
}

void readRpm() {
  numBangs = 0;
  attachInterrupt(digitalPinToInterrupt(2), pointsOpening, RISING);
  delay(200);
  detachInterrupt(0);
  unsigned int rpm = ((60000/200)*numBangs)/2;
  Serial.print("RPM ");
  Serial.print(rpm);
  Serial.print("\n");
}

int counter = 0;
void loop() {
  if (++counter%3 == 0) {
    readSensorsData();
  }
  readGpsData();
  readRpm();
}






#include <SoftwareSerial.h>
#include "TinyGPS++.h"

SoftwareSerial gpsSerial(10, 11); //rx,tx
TinyGPSPlus gps;

#include "gps_readings.h"
#include "sensor_readings.h"
#include "tachometer.h"

#include "TinyGPS++.h"


void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  delay(1000);

  //Setup digital pins for tacho
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
}


int counter = 0;
//Read GPS data as often as possible not to miss anything
void loop() {
  parseGpsData(&gpsSerial, &gps);
  if (++counter%3 == 0) {
    sendRawReadings();
    sendSensorsData();
    parseGpsData(&gpsSerial, &gps);
  }
  sendRpmReading();
  parseGpsData(&gpsSerial, &gps);
  sendGpsData(&gps);

  for (int i = 0; i < 10; ++i) {
    parseGpsData(&gpsSerial, &gps);
    delay(50);  
  }
}


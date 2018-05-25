
#include <SoftwareSerial.h>
SoftwareSerial gpsSerial(10, 11); //rx,tx

#include "gps_readings.h"
#include "sensor_readings.h"
#include "tachometer.h"

#include "TinyGPS++.h"


void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);

  //Setup digital pins for tacho
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
}


int counter = 0;
void loop() {
  if (++counter%3 == 0) {
    sendSensorsData();
  }
  sendRpmReading();
  sendGpsData(gpsSerial);
  delay(100);
}





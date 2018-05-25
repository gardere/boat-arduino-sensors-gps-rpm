#include "Arduino.h"
#include "tachometer.h"


volatile unsigned long numBangs = 0;
unsigned long lastRpmSampling;

void pointsOpening() {
    ++numBangs;
}

void sendRpmReading() {
  unsigned int numberOfCylinders = 4;
  if (lastRpmSampling > 0) {
    detachInterrupt(digitalPinToInterrupt(2));
    unsigned long samplingTime = millis() - lastRpmSampling;
    unsigned long rpm = ((60000/samplingTime)*numBangs)/(numberOfCylinders/2);
    Serial.print("RPM ");
    Serial.print(rpm);
    Serial.print("\n");
  }
  lastRpmSampling = millis();
  numBangs = 0;
  attachInterrupt(digitalPinToInterrupt(2), pointsOpening, RISING);
  delay(200);
}


#include "Arduino.h"
#include "tachometer.h"


unsigned long samplingPeriodMs = 400;
unsigned int numberOfCylinders = 4;

volatile unsigned long numBangs = 0;

void pointsOpening() {
    ++numBangs;
}

void sendRpmReading() {
  numBangs = 0;
  attachInterrupt(digitalPinToInterrupt(2), pointsOpening, RISING);
  delay(samplingPeriodMs);
  detachInterrupt(digitalPinToInterrupt(2));

  unsigned long rpm = ((60000/samplingPeriodMs)*numBangs)/(numberOfCylinders/2);
  Serial.print("RPM ");
  Serial.print(rpm);
  Serial.print("\n");
}


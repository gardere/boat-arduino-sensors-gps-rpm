#include "sensor_readings.h"
#include "Arduino.h"


int voltagePin = A1;
float TOP_RESISTOR_VALUE = 110.0f; //aka R1  in voltage divider equation
int sensorPins[4] = { A2, A3, A4, A5 };
int numberOfSensors = sizeof(sensorPins) / sizeof(sensorPins[0]);

float fullVoltage = 3.2f;


float getSensorVoltage(int pinNumber) {
   float vout = analogRead(pinNumber);
   return vout / 1024.0f * (1000 + 2200) / 1000 * fullVoltage; //we are returning Vin, the input voltage before going through the divider
}

unsigned int getSensorResistance(int pinNumber) {
  float rawReading = analogRead(pinNumber) / 1024.0f * 5.0f; //aka Vout  in voltage divider equation - arduino analog inputs readings return a number of (5V / 1024 'steps')

  return (unsigned int)(rawReading * TOP_RESISTOR_VALUE / (fullVoltage - rawReading)); // we assume Vin is divided by a stable and precise Arduino voltage output
}

void sendSensorsData() {
  Serial.print("RDG ");
  Serial.print(getSensorVoltage(voltagePin));
  Serial.print(" ");
  for(int i=0; i<numberOfSensors; ++i) {
    Serial.print(getSensorResistance(sensorPins[i]));
    Serial.print(" ");
  }
  Serial.print("\n");
}


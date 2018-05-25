#include "Arduino.h"
#include "sensor_readings.h"


int voltagePin = A1;
float TOP_RESISTOR_VALUE = 110.0f; //aka R1  in voltage divider equation
int sensorPins[4] = { A2, A3, A4, A5 };
int numberOfSensors = sizeof(sensorPins) / sizeof(sensorPins[0]);


float getSensorVoltage(int pinNumber) {
   float vout = analogRead(pinNumber);
   return vout * 3.2f; //we are returning Vin, the input voltage before going through the divider
}

float getSensorResistance(int pinNumber) {
  //TODO: apply voltage divider formula to output a result in ohms

  float rawReading = analogRead(pinNumber); //aka Vout  in voltage divider equation
  return rawReading * TOP_RESISTOR_VALUE  / (5.0f - rawReading); // we assume Vin is divided by a stable and precise 5V Arduino output
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


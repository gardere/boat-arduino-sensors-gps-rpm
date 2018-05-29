#include "gps_readings.h"

void parseGpsData(SoftwareSerial *gpsSerial, TinyGPSPlus *gps) {
  unsigned long startTime = millis();
  
  while (gpsSerial->available() && (millis() - startTime < 5000)) { // don't spend more than 1 second readings GPS data
    char a = gpsSerial->read();
    gps->encode(a);
  }
}

void sendGpsData(TinyGPSPlus *gps) {
//  Serial.println("\n--------------");

//  if (gps->location.isUpdated()) {
    Serial.print("GPS ");
    Serial.print(gps->location.lng(), 10); // Longitude in degrees (double)
    Serial.print(" ");
    Serial.print(gps->location.lat(), 10); // Latitude in degrees (double)
    Serial.print(" ");
    Serial.print (gps->speed.kmph() > 3.0 ? gps->speed.kmph() : 0);
    Serial.print(" ");
    Serial.print(gps->course.deg());
    Serial.print(" ");
    Serial.print(gps->satellites.value());
    Serial.print(" ");
    Serial.print(gps->hdop.hdop());
    Serial.print(" ");
    
    Serial.print(gps->date.year());
    Serial.print(",");
    Serial.print(gps->date.month());
    Serial.print(",");
    Serial.print(gps->date.day());
    Serial.print(",");
    Serial.print(gps->time.hour());
    Serial.print(",");
    Serial.print(gps->time.minute());
    Serial.print(",");
    Serial.print(gps->time.second());
    Serial.print(",");
    Serial.print(gps->time.centisecond());
    Serial.print("0");


    Serial.print(" ");
    Serial.print(gps->failedChecksum());
    Serial.println("");
//  }
}

#include "TinyGPS++.h"
#include "gps_readings.h"

TinyGPSPlus gps;


void sendGpsData(SoftwareSerial gpsSerial) {
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

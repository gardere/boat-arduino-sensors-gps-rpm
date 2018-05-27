#include <SoftwareSerial.h>
#include "TinyGPS++.h"

void parseGpsData(SoftwareSerial *gpsSerial, TinyGPSPlus *gps);
void sendGpsData(TinyGPSPlus *tinyGps);

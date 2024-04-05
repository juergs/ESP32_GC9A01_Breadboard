#include "gps.h"

#include <Arduino.h>

const float EARH_RADIUS = 6371.0;

void GPS::displayInfo() {
  Serial.println(F("Location: "));
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    Serial.print(" Speed: ");
    Serial.print(gps.speed.kmph());
    Serial.print(" Date/Time: ");
    Serial.print(gps.date.value());
    Serial.print(" Satellites: ");
    Serial.print(gps.satellites.value());
    Serial.print(" Altitude: ");
    Serial.print(gps.altitude.meters());
    Serial.println(" ");
  } 
  else 
  {
    Serial.println(F("INVALID"));
  }
}
double degreesToRadians(double degrees) { return degrees * M_PI / 180.0; }

int GPS::distance(float lat, float lon) {
  float lat1 = gps.location.lat();
  float lon1 = gps.location.lng();
  float lat2 = lat;
  float lon2 = lon;
  return calculateDistance(lat1, lon1, lat2, lon2);
}

int GPS::calculateDistance(float lat1, float lon1, float lat2, float lon2) {
  lat1 = degreesToRadians(lat1);
  lon1 = degreesToRadians(lon1);
  lat2 = degreesToRadians(lat2);
  lon2 = degreesToRadians(lon2);

  double dlat = lat2 - lat1;
  double dlon = lon2 - lon1;
  double a = std::sin(dlat / 2.0) * std::sin(dlat / 2.0) +
             std::cos(lat1) * std::cos(lat2) * std::sin(dlon / 2.0) *
                 std::sin(dlon / 2.0);
  double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

  // Distance in kilometers
  double distance = EARH_RADIUS * c * 1000.0;  // Convert to meters

  return distance;
}

int GPS::calculateAngle(float lat1, float lon1, float lat2, float lon2) 
{
  lat1 = degreesToRadians(lat1);
  lon1 = degreesToRadians(lon1);
  lat2 = degreesToRadians(lat2);
  lon2 = degreesToRadians(lon2);

  // Calculate the differences
  double dLon = lon2 - lon1;

  // Calculate the initial bearing using the Haversine formula
  double y = sin(dLon) * cos(lat2);
  double x = cos(lat1) * sin(lat2) - (sin(lat1) * cos(lat2) * cos(dLon));
  double initialBearing = atan2(y, x);

  // Convert the initial bearing from radians to degrees
  initialBearing = fmod((initialBearing + 2.0 * M_PI), (2.0 * M_PI));
  initialBearing = initialBearing * (180.0 / M_PI);
  // Adjust the angle to be relative to the north (clockwise from positive X-axis)
  initialBearing = 90.0 - initialBearing;

  // Ensure the result is in the range [0, 360)
  if (initialBearing < 0.0) 
  {
    initialBearing += 360.0;
  }

  return initialBearing;
}

Location getEmptyLocation() 
{
  Location location;
  location.lat = 0;
  location.lon = 0;
  return location;
}

Location GPS::getLocation() {
  while (Serial2.available() > 0) 
  {

    
    if (gps.encode(Serial2.read())) 
    {
      displayInfo();
      if (gps.location.isValid()) 
      {
        Location location;
        location.lat = gps.location.lat();
        location.lon = gps.location.lng();
        return location;
      }
      else 
      {
        return getEmptyLocation();
      }
    }
  }
  return getEmptyLocation();
}

void GPS::init() {
  Serial2.begin(9600);
  Serial.println(F("GPS module is ready"));
}

void GPS::updateSerial() {
  delay(500);
  while (Serial.available()) {
    Serial2.write(
        Serial.read());  // Forward what Serial received to Software Serial Port
  }
  while (Serial2.available()) {
    Serial.write(
        Serial2
            .read());  // Forward what Software Serial received to Serial Port
  }
}

/*Serial.println(gps.location.lat(), 6); // Latitude in degrees (double)
Serial.println(gps.location.lng(), 6); // Longitude in degrees (double)
Serial.print(gps.location.rawLat().negative ? "-" : "+");
Serial.println(gps.location.rawLat().deg); // Raw latitude in whole degrees
Serial.println(gps.location.rawLat().billionths);// ... and billionths (u16/u32)
Serial.print(gps.location.rawLng().negative ? "-" : "+");
Serial.println(gps.location.rawLng().deg); // Raw longitude in whole degrees
Serial.println(gps.location.rawLng().billionths);// ... and billionths (u16/u32)
Serial.println(gps.date.value()); // Raw date in DDMMYY format (u32)
Serial.println(gps.date.year()); // Year (2000+) (u16)
Serial.println(gps.date.month()); // Month (1-12) (u8)
Serial.println(gps.date.day()); // Day (1-31) (u8)
Serial.println(gps.time.value()); // Raw time in HHMMSSCC format (u32)
Serial.println(gps.time.hour()); // Hour (0-23) (u8)
Serial.println(gps.time.minute()); // Minute (0-59) (u8)
Serial.println(gps.time.second()); // Second (0-59) (u8)
Serial.println(gps.time.centisecond()); // 100ths of a second (0-99) (u8)
Serial.println(gps.speed.value()); // Raw speed in 100ths of a knot (i32)
Serial.println(gps.speed.knots()); // Speed in knots (double)
Serial.println(gps.speed.mph()); // Speed in miles per hour (double)
Serial.println(gps.speed.mps()); // Speed in meters per second (double)
Serial.println(gps.speed.kmph()); // Speed in kilometers per hour (double)
Serial.println(gps.course.value()); // Raw course in 100ths of a degree (i32)
Serial.println(gps.course.deg()); // Course in degrees (double)
Serial.println(gps.altitude.value()); // Raw altitude in centimeters (i32)
Serial.println(gps.altitude.meters()); // Altitude in meters (double)
Serial.println(gps.altitude.miles()); // Altitude in miles (double)
Serial.println(gps.altitude.kilometers()); // Altitude in kilometers (double)
Serial.println(gps.altitude.feet()); // Altitude in feet (double)
Serial.println(gps.satellites.value()); // Number of satellites in use (u32)
Serial.println(gps.hdop.value()); // Horizontal Dim. of Precision (100ths-i32)*/
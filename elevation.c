#include <Arduino.h>

// Function to calculate the solar declination
float calculateSolarDeclination(int dayOfYear) {
  return 23.45 * sin(((360.0 / 365.0) * (dayOfYear - 81)) * (PI / 180));
}

// Function to calculate the hour angle
float calculateHourAngle(float localDecimalHours, float longitude) {
  float timeCorrection = (longitude - 15 * round(longitude / 15)) / 15;
  float solarTime = localDecimalHours + timeCorrection;
  return 15 * (solarTime - 12) * (PI / 180); // Convert to radians
}

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for the serial port to connect - only needed for native USB

  float latitude = 46.3091; // North Bay latitude
  float longitude = -79.4608; // North Bay longitude
  int dayOfYear = 59; // Example: February 28th is the 59th day of a non-leap year
  float localDecimalHours = 11.5; // 11:30 AM in decimal hours

  float solarDeclination = calculateSolarDeclination(dayOfYear) * (PI / 180); // Convert to radians
  float hourAngle = calculateHourAngle(localDecimalHours, longitude);

  float latitudeRad = latitude * (PI / 180); // Convert to radians

  // Calculate the solar elevation angle
  float solarElevation = asin(sin(solarDeclination) * sin(latitudeRad) + 
                              cos(solarDeclination) * cos(latitudeRad) * cos(hourAngle));

  // Convert the solar elevation from radians to degrees
  float solarElevationDeg = solarElevation * (180 / PI);

  Serial.print("Solar Elevation Angle at 11:30 AM local time: ");
  Serial.print(solarElevationDeg);
  Serial.println(" degrees");
}

void loop() {
  // Not used in this example
}

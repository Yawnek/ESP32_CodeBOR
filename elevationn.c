#include <cmath>

// Constants
const float globalLatitude = 46.3; // North Bay latitude
const float globalLongitude = -79.46; // North Bay longitude

// Function to calculate solar declination
float calculateSolarDeclination(int dayOfYear) {
  // Calculate the declination angle (delta), in degrees
  return 23.45 * sin(((360.0 / 365.0) * (dayOfYear - 81)) * (M_PI / 180));
}

// Function to calculate the hour angle
float calculateHourAngle(float localDecimalHours) {
  // Calculate the correction for the local time, based on the longitude
  float timeCorrection = (globalLongitude - 15 * round(globalLongitude / 15)) / 15;
  // Calculate the local solar time
  float solarTime = localDecimalHours + timeCorrection;
  // Convert the solar time to the hour angle, in radians
  return 15 * (solarTime - 12) * (M_PI / 180);
}

// Function to calculate solar elevation
float calculateSolarElevation(float declination, float hourAngle) {
  // Convert angles from degrees to radians for computation
  float declinationRad = declination * M_PI / 180.0;
  float latitudeRad = globalLatitude * M_PI / 180.0;

  // Calculate solar elevation angle in radians
  float elevationRad = asin(sin(declinationRad) * sin(latitudeRad) + 
                            cos(declinationRad) * cos(latitudeRad) * cos(hourAngle));

  // Convert the result back to degrees
  float elevationDeg = elevationRad * 180.0 / M_PI;
  return elevationDeg;
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Calculate the declination angle and hour angle for April 24, 2024, at 11:11 AM
  int dayOfYear = 114; // April 24
  float localTime = 11.0 + (11.0 / 60.0); // Convert 11:11 AM to decimal hours
  
  float declination = calculateSolarDeclination(dayOfYear);
  float hourAngle = calculateHourAngle(localTime);
  
  // Calculate and print the solar elevation angle
  float solarElevation = calculateSolarElevation(declination, hourAngle);
  Serial.print("Solar Elevation: ");
  Serial.println(solarElevation);
}

void loop() {
  // No action needed in loop
}

#include <Wire.h>
#include <JY901.h>

void setup() {
  // Initialize the serial communication at a baud rate of 115200
  Serial.begin(115200);  
  delay(1000); // Wait for the serial port to initialize

  // Test print to verify basic functionality
  Serial.println("Testing Serial Output...");
}

void loop() {
  while (Serial.available()) {
    JY901.CopeSerialData(Serial.read()); // Call JY901 data cope function
  }

  // Print Time
  Serial.print("Time:20");
  Serial.print(JY901.stcTime.ucYear); Serial.print("-");
  Serial.print(JY901.stcTime.ucMonth); Serial.print("-");
  Serial.print(JY901.stcTime.ucDay); Serial.print(" ");
  Serial.print(JY901.stcTime.ucHour); Serial.print(":");
  Serial.print(JY901.stcTime.ucMinute); Serial.print(":");
  Serial.println((float)JY901.stcTime.ucSecond + (float)JY901.stcTime.usMiliSecond / 1000);
  
  // Print Acceleration
  Serial.print("Acc:");
  Serial.print((float)JY901.stcAcc.a[0]/32768*16); Serial.print(" ");
  Serial.print((float)JY901.stcAcc.a[1]/32768*16); Serial.print(" ");
  Serial.println((float)JY901.stcAcc.a[2]/32768*16);
  
  // Print Gyroscope
  Serial.print("Gyro:");
  Serial.print((float)JY901.stcGyro.w[0]/32768*2000); Serial.print(" ");
  Serial.print((float)JY901.stcGyro.w[1]/32768*2000); Serial.print(" ");
  Serial.println((float)JY901.stcGyro.w[2]/32768*2000);
  
  // Print Angle
  Serial.print("Angle:");
  Serial.print((float)JY901.stcAngle.Angle[0]/32768*180); Serial.print(" ");
  Serial.print((float)JY901.stcAngle.Angle[1]/32768*180); Serial.print(" ");
  Serial.println((float)JY901.stcAngle.Angle[2]/32768*180);
  
  // Print Magnetic Field
  Serial.print("Mag:");
  Serial.print(JY901.stcMag.h[0]); Serial.print(" ");
  Serial.print(JY901.stcMag.h[1]); Serial.print(" ");
  Serial.println(JY901.stcMag.h[2]);
  
  // Print Pressure and Altitude
  Serial.print("Pressure:");
  Serial.print(JY901.stcPress.lPressure); Serial.print(" ");
  Serial.println((float)JY901.stcPress.lAltitude/100);
  
  // Print DStatus
  Serial.print("DStatus:");
  Serial.print(JY901.stcDStatus.sDStatus[0]); Serial.print(" ");
  Serial.print(JY901.stcDStatus.sDStatus[1]); Serial.print(" ");
  Serial.print(JY901.stcDStatus.sDStatus[2]); Serial.print(" ");
  Serial.println(JY901.stcDStatus.sDStatus[3]);
  
  // Print GPS Longitude and Latitude
  Serial.print("Longitude:");
  Serial.print(JY901.stcLonLat.lLon / 10000000); Serial.print("Deg");
  Serial.print((double)(JY901.stcLonLat.lLon % 10000000) / 1e5); Serial.print("m Latitude:");
  Serial.print(JY901.stcLonLat.lLat / 10000000); Serial.print("Deg");
  Serial.println((double)(JY901.stcLonLat.lLat % 10000000) / 1e5); Serial.println("m");
  
  // Print GPS Height, Yaw, and Velocity
  Serial.print("GPSHeight:");
  Serial.print((float)JY901.stcGPSV.sGPSHeight / 10); Serial.print("m GPSYaw:");
  Serial.print((float)JY901.stcGPSV.sGPSYaw / 10); Serial.print("Deg GPSV:");
  Serial.println((float)JY901.stcGPSV.lGPSVelocity / 1000); Serial.println("km/h");
  
  // Print Satellite Number and DOP Values
  Serial.print("SN:");
  Serial.print(JY901.stcSN.sSVNum); Serial.print(" PDOP:");
  Serial.print((float)JY901.stcSN.sPDOP / 100); Serial.print(" HDOP:");
  Serial.print((float)JY901.stcSN.sHDOP / 100); Serial.print(" VDOP:");
  Serial.println((float)JY901.stcSN.sVDOP / 100);
  
  Serial.println("");
  delay(500);
}

#include <Wire.h>
#include "MPU9250.h"  

MPU9250 mpu; // Declare the MPU9250 object

void setup() {
    Wire.begin(); // Initialize the I2C communication
    if (!mpu.setup(0x68)) { // Setup the MPU9250, assuming 0x68 is the I2C address
        Serial.println("MPU9250 setup failed");
        while (1); // Halt if failed
    }
    // Additional setup code...
}

void loop() {
    // Code to read data from MPU9250
}

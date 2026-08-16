#include "LSM6DS3.h"
#include "Wire.h"

// Create IMU object.
// I2C address for the LSM6DS3TR-C is normally 0x6A.
LSM6DS3 myIMU(I2C_MODE, 0x6A);

// Print interval in milliseconds.
// 20 ms = 50 samples/second.
const unsigned long SAMPLE_INTERVAL_MS = 20;

unsigned long lastSampleTime = 0;

void setup()
{
  Serial.begin(115200);

  // Give the USB serial connection a moment to start.
  delay(1000);

  Serial.println();
  Serial.println("=================================");
  Serial.println("Wizard Wand - IMU Prototype 1");
  Serial.println("=================================");

  // Initialize the IMU.
  if (myIMU.begin() != 0)
  {
    Serial.println("ERROR: IMU initialization failed!");
    Serial.println("Check board selection and library installation.");
    
    while (1)
    {
      delay(1000);
    }
  }

  Serial.println("IMU initialized successfully.");
  Serial.println();
  Serial.println("Accel (g)              Gyro (dps)");
  Serial.println("X       Y       Z      X       Y       Z");
}

void loop()
{
  unsigned long currentTime = millis();

  // Limit output to SAMPLE_INTERVAL_MS.
  if (currentTime - lastSampleTime < SAMPLE_INTERVAL_MS)
  {
    return;
  }

  lastSampleTime = currentTime;

  // Read accelerometer.
  float ax = myIMU.readFloatAccelX();
  float ay = myIMU.readFloatAccelY();
  float az = myIMU.readFloatAccelZ();

  // Read gyroscope.
  float gx = myIMU.readFloatGyroX();
  float gy = myIMU.readFloatGyroY();
  float gz = myIMU.readFloatGyroZ();

  // Calculate total acceleration magnitude.
  float accelerationMagnitude =
      sqrt(ax * ax + ay * ay + az * az);

  // Calculate total rotational velocity.
  float gyroMagnitude =
      sqrt(gx * gx + gy * gy + gz * gz);

  // Print the raw values.
  Serial.print(ax, 3);
  Serial.print("\t");

  Serial.print(ay, 3);
  Serial.print("\t");

  Serial.print(az, 3);
  Serial.print("\t");

  Serial.print(gx, 2);
  Serial.print("\t");

  Serial.print(gy, 2);
  Serial.print("\t");

  Serial.print(gz, 2);
  Serial.print("\t");

  // Print calculated values.
  Serial.print(" | Accel=");
  Serial.print(accelerationMagnitude, 3);

  Serial.print(" | Gyro=");
  Serial.print(gyroMagnitude, 2);

  Serial.println();
}
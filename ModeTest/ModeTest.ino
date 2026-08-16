#include "LSM6DS3.h"
#include "Wire.h"

// ============================================================
// WIZARD WAND - PROTOTYPE 2
//
// Hardware:
//
//   D0 -> LEARN button -> GND
//   D1 -> CAST button  -> GND
//
// Onboard RGB LED:
//
//   RED   = idle
//   BLUE  = learning
//   GREEN = casting
//
// Buttons use INPUT_PULLUP:
//
//   Button released = HIGH
//   Button pressed  = LOW
//
// The onboard RGB LED is common-anode:
//
//   LOW  = LED ON
//   HIGH = LED OFF
// ============================================================


// ------------------------------------------------------------
// IMU
// ------------------------------------------------------------

LSM6DS3 myIMU(I2C_MODE, 0x6A);

// Read the IMU every 20 milliseconds.
// 20 ms = 50 samples per second.
const unsigned long SAMPLE_INTERVAL_MS = 20;

unsigned long lastSampleTime = 0;


// ------------------------------------------------------------
// BUTTONS
// ------------------------------------------------------------

const int LEARN_BUTTON = 0;  // D0
const int CAST_BUTTON  = 1;  // D1

bool learnReported = false;
bool castReported  = false;


// ------------------------------------------------------------
// RGB LED
//
// These are the onboard RGB LED pins defined by the XIAO
// nRF52840 Arduino board package.
//
// The LED is common-anode, so LOW turns a color ON.
// ------------------------------------------------------------

const int RED_LED   = LED_RED;
const int GREEN_LED = LED_GREEN;
const int BLUE_LED  = LED_BLUE;


// ------------------------------------------------------------
// SET LED COLOR
// ------------------------------------------------------------

void setLED(bool red, bool green, bool blue)
{
  // Common-anode LED:
  //
  // LOW  = ON
  // HIGH = OFF

  digitalWrite(RED_LED,   red   ? LOW : HIGH);
  digitalWrite(GREEN_LED, green ? LOW : HIGH);
  digitalWrite(BLUE_LED,  blue  ? LOW : HIGH);
}


// ------------------------------------------------------------
// SETUP
// ------------------------------------------------------------

void setup()
{
  Serial.begin(115200);

  // Give the computer time to establish the USB serial
  // connection.
  delay(1000);

  Serial.println();
  Serial.println("=================================");
  Serial.println("   WIZARD WAND - PROTOTYPE 2");
  Serial.println("=================================");
  Serial.println();


  // ----------------------------------------------------------
  // Configure buttons
  // ----------------------------------------------------------

  pinMode(LEARN_BUTTON, INPUT_PULLUP);
  pinMode(CAST_BUTTON, INPUT_PULLUP);


  // ----------------------------------------------------------
  // Configure RGB LED
  // ----------------------------------------------------------

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);


  // Start in IDLE state = RED
  setLED(true, false, false);


  // ----------------------------------------------------------
  // Initialize IMU
  // ----------------------------------------------------------

  if (myIMU.begin() != 0)
  {
    Serial.println("ERROR: IMU initialization failed!");
    Serial.println("Check your board selection and IMU library.");

    // Show an error by flashing red/blue.
    while (1)
    {
      setLED(true, false, false);
      delay(250);

      setLED(false, false, true);
      delay(250);
    }
  }


  Serial.println("IMU initialized successfully.");
  Serial.println();

  Serial.println("BUTTONS:");
  Serial.println("  D0 = LEARN");
  Serial.println("  D1 = CAST");
  Serial.println();

  Serial.println("LED STATES:");
  Serial.println("  RED   = IDLE");
  Serial.println("  BLUE  = LEARNING");
  Serial.println("  GREEN = CASTING");
  Serial.println();

  Serial.println("IMU DATA:");
  Serial.println("Accel X   Accel Y   Accel Z   Gyro X   Gyro Y   Gyro Z");
  Serial.println();
}


// ------------------------------------------------------------
// MAIN LOOP
// ------------------------------------------------------------

void loop()
{
  checkButtons();
  readIMU();
}


// ------------------------------------------------------------
// BUTTON HANDLING
// ------------------------------------------------------------

void checkButtons()
{
  bool learnPressed = (digitalRead(LEARN_BUTTON) == LOW);
  bool castPressed  = (digitalRead(CAST_BUTTON) == LOW);


  // ----------------------------------------------------------
  // LED STATE
  //
  // LEARN takes priority if both buttons are pressed.
  // ----------------------------------------------------------

  if (learnPressed)
  {
    // BLUE = learning
    setLED(false, false, true);
  }
  else if (castPressed)
  {
    // GREEN = casting
    setLED(false, true, false);
  }
  else
  {
    // RED = idle
    setLED(true, false, false);
  }


  // ----------------------------------------------------------
  // LEARN BUTTON MESSAGE
  // ----------------------------------------------------------

  if (learnPressed && !learnReported)
  {
    Serial.println();
    Serial.println(">>> LEARN BUTTON PRESSED <<<");
    Serial.println("LED = BLUE");
    Serial.println("Ready to record a gesture.");

    learnReported = true;
  }

  if (!learnPressed)
  {
    learnReported = false;
  }


  // ----------------------------------------------------------
  // CAST BUTTON MESSAGE
  // ----------------------------------------------------------

  if (castPressed && !castReported)
  {
    Serial.println();
    Serial.println(">>> CAST BUTTON PRESSED <<<");
    Serial.println("LED = GREEN");
    Serial.println("Ready to recognize a gesture.");

    castReported = true;
  }

  if (!castPressed)
  {
    castReported = false;
  }
}


// ------------------------------------------------------------
// IMU READING
// ------------------------------------------------------------

void readIMU()
{
  unsigned long currentTime = millis();

  // Don't read faster than our desired sample rate.
  if (currentTime - lastSampleTime < SAMPLE_INTERVAL_MS)
  {
    return;
  }

  lastSampleTime = currentTime;


  // ----------------------------------------------------------
  // ACCELEROMETER
  //
  // Values are in units of g.
  // ----------------------------------------------------------

  float ax = myIMU.readFloatAccelX();
  float ay = myIMU.readFloatAccelY();
  float az = myIMU.readFloatAccelZ();


  // ----------------------------------------------------------
  // GYROSCOPE
  //
  // Values are in degrees per second.
  // ----------------------------------------------------------

  float gx = myIMU.readFloatGyroX();
  float gy = myIMU.readFloatGyroY();
  float gz = myIMU.readFloatGyroZ();


  // ----------------------------------------------------------
  // CALCULATE MAGNITUDES
  // ----------------------------------------------------------

  float accelerationMagnitude =
    sqrt(ax * ax + ay * ay + az * az);

  float gyroMagnitude =
    sqrt(gx * gx + gy * gy + gz * gz);


  // ----------------------------------------------------------
  // PRINT DATA
  // ----------------------------------------------------------

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

  Serial.print("\t | Accel=");
  Serial.print(accelerationMagnitude, 3);

  Serial.print(" | Gyro=");
  Serial.println(gyroMagnitude, 2);
}
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
const int heartRatePotPin = A0;    // Potentiometer for heart rate
const int temperaturePotPin = A1;   // Potentiometer for body temperature
const int greenLedPin = 12;         // Green LED for safety indication
const int redLedPin = 13;           // Red LED for warning indication

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  mpu.initialize();
  
  // Set the sensor sensitivity scale to +/-8g
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);

  pinMode(greenLedPin, OUTPUT);    // Green LED pin as output
  pinMode(redLedPin, OUTPUT);      // Red LED pin as output
}

void loop() {
  // Read accelerometer data
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Calculate magnitude
  float magnitude = sqrt(ax*ax + ay*ay + az*az);

  // Set threshold value for movement (fall detection)
  float movementThreshold = 20.0; // Adjust as needed

  // Read heart rate from potentiometer
  int heartRate = map(analogRead(heartRatePotPin), 0, 1023, 0, 100); // Assuming 0-100 BPM

  // Set threshold value for heart rate (adjust as needed)
  int heartRateThreshold = 80; // Example threshold, adjust as needed

  // Read body temperature from potentiometer
  int temperature = map(analogRead(temperaturePotPin), 0, 1023, 0, 100); // Assuming 0-100°C

  // Set threshold value for body temperature (adjust as needed)
  int temperatureThreshold = 37; // Example threshold, adjust as needed

  // Safety status logic
  if (magnitude > movementThreshold || heartRate > heartRateThreshold || temperature > temperatureThreshold) {
    digitalWrite(greenLedPin, LOW); // Turn off green LED (unsafe)
    digitalWrite(redLedPin, HIGH); // Turn on red LED (warning)
  } else {
    digitalWrite(greenLedPin, HIGH); // Turn on green LED (safe)
    digitalWrite(redLedPin, LOW); // Turn off red LED
  }

  delay(100); // Adjust delay as needed
}

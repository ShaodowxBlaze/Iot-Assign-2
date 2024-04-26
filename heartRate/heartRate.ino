
int potentiometerPin = A0; // analog pin for potentiometer
int redLedPin = 5;         // pin number for red LED
int yellowLedPin = 6;      // pin number for yellow LED
int greenLedPin = 7;       // pin number for green LED

void setup() {
  pinMode(potentiometerPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  // Read the potentiometer value
  int sensorValue = analogRead(potentiometerPin);

  // Map the potentiometer value to a range suitable for heart rate simulation
  int heartRate = map(sensorValue, 0, 1023, 0, 160); // Assume a heart rate range of 40 to 160 BPM

  // Define thresholds for different heart rate conditions
  int severeTachycardiaThreshold = 150;
  int mildTachycardiaThreshold = 120;
  int mildBradycardiaThreshold = 60;
  int severeBradycardiaThreshold = 50;

  // Determine which LED to light up based on heart rate
  if (heartRate >= severeTachycardiaThreshold || heartRate <= severeBradycardiaThreshold) {
    // Red LED lights up for cardiac arrest, severe bradycardia, and severe tachycardia
    digitalWrite(redLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    Serial.print("Heart Rate: ");
    Serial.println(heartRate);
  } else if (heartRate >= mildTachycardiaThreshold || heartRate <= mildBradycardiaThreshold) {
    // Yellow LED lights up for mild bradycardia and mild tachycardia
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    Serial.print("Heart Rate: ");
    Serial.println(heartRate);
  } else {
    // Green LED lights up for normal heart rate
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    Serial.print("Heart Rate: ");
    Serial.println(heartRate);
  }
}
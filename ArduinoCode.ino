int potentiometerPin1 = A0; // analog pin for potentiometer 1 (body temperature)
int potentiometerPin2 = A1; // analog pin for potentiometer 2 (heart rate)
int redLedPin = 5;          // pin number for red LED
int yellowLedPin = 6;       // pin number for yellow LED
int greenLedPin = 7;        // pin number for green LED
int buttonPin = 8;          // pin number for button
int buttonState = 0;        // variable to store button state
int fallDetected = 0;  
int redLedStatus = 0;      // variable to store red LED status
int yellowLedStatus = 0;    // variable to store yellow LED status
int greenLedStatus = 0;     // variable to store green LED status

void setup() {
  pinMode(potentiometerPin1, INPUT);
  pinMode(potentiometerPin2, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  // Read the potentiometer values
  int sensorValue1 = analogRead(potentiometerPin1); // For body temperature
  int sensorValue2 = analogRead(potentiometerPin2); // For heart rate

  // Map the potentiometer value for heart rate simulation
  int heartRate = map(sensorValue2, 0, 1023, 0, 160); // Assume a heart rate range of 0 to 160 BPM

  // Map the potentiometer value for body temperature simulation
  float temperature = map(sensorValue1, 0, 1023, 32, 42); // Assume a body temperature range of 32.0 C to 42.0 C

  // Define thresholds for different heart rate conditions
  int severeTachycardiaThreshold = 150;
  int mildTachycardiaThreshold = 120;
  int mildBradycardiaThreshold = 60;
  int severeBradycardiaThreshold = 50;

  // Define thresholds for different body temperature conditions
  float hyperpyrexiaThreshold = 40.0;
  float feverThreshold = 38.0;
  float hypothermiaThreshold = 35.0;
  float mildFeverThreshold = 37.0;
  float mildHypothermiaThreshold = 36.0;

  // Read button state
  buttonState = digitalRead(buttonPin);

  // Check if the fall detection button is pressed
  if (buttonState == HIGH) {
    fallDetected = 1;
    Serial.println("Fall Detected !!!!");
  } else {
    fallDetected = 0;
  }

  // Determine LED color based on heart rate and temperature
  switch (fallDetected) {
    case 1:
      // Red LED lights up for severe conditions or fall detection
      digitalWrite(redLedPin, HIGH);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(greenLedPin, LOW);
      redLedStatus = 1;
      yellowLedStatus = 0;
      greenLedStatus = 0;
      Serial.println("Status: Severe Condition  ");
      break;
    default:
      if (heartRate >= severeTachycardiaThreshold || heartRate <= severeBradycardiaThreshold || temperature >= hyperpyrexiaThreshold || temperature <= hypothermiaThreshold) {
        // Red LED lights up for severe conditions
        digitalWrite(redLedPin, HIGH);
        digitalWrite(yellowLedPin, LOW);
        digitalWrite(greenLedPin, LOW);
        redLedStatus = 1;
        yellowLedStatus = 0;
        greenLedStatus = 0;
        Serial.println("Status: Severe Condition  ");
      } else if ((heartRate >= mildTachycardiaThreshold || heartRate <= mildBradycardiaThreshold) || (temperature >= feverThreshold || temperature <= mildHypothermiaThreshold)) {
        // Yellow LED lights up for mild conditions
        digitalWrite(redLedPin, LOW);
        digitalWrite(yellowLedPin, HIGH);
        digitalWrite(greenLedPin, LOW);
        redLedStatus = 0;
        yellowLedStatus = 1;
        greenLedStatus = 0;
        Serial.println("Status: Mild Condition  ");
      } else {
        // Green LED lights up for normal conditions
        digitalWrite(redLedPin, LOW);
        digitalWrite(yellowLedPin, LOW);
        digitalWrite(greenLedPin, HIGH);
        redLedStatus = 0;
        yellowLedStatus = 0;
        greenLedStatus = 1;
        Serial.println("Status: Normal  ");
      }
  }

  // Send sensor data over serial connection
  Serial.print("FallDetection: ");
  Serial.print(fallDetected ? 1 : 0);
  Serial.print(", HeartRate: ");
  Serial.print(heartRate);
  Serial.print(" BPM, Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  delay(1000); // Delay for better readability in serial monitor
}

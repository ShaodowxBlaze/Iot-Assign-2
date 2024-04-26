int LED_Green = 7;
int LED_Yellow = 6;
int LED_Red = 5;
int fallDetection = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_Green,OUTPUT);
  pinMode(LED_Yellow,OUTPUT);
  pinMode(LED_Red,OUTPUT);
  pinMode(fallDetection,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int Fall = digitalRead(fallDetection);

  if(Fall == 1){
    digitalWrite(LED_Green,LOW);
    digitalWrite(LED_Yellow,LOW);
    digitalWrite(LED_Red,HIGH);
    Serial.println("Fall Detected");
  }
  else
  {
    digitalWrite(LED_Green,HIGH);
    digitalWrite(LED_Yellow,LOW);
    digitalWrite(LED_Red,LOW);
  }
}

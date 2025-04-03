unsigned long currentTime = 0;

int sensorPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  currentTime = millis();

  sensorValue = analogRead(A0);

  serialTask();
}

void serialTask() {
  static unsigned long serialLast = 0;
  int serialDelay = 100;

  if (currentTime - serialLast >= serialDelay) {
    serialLast = currentTime;
    
    Serial.print("Potentiometre:");
    Serial.println(sensorValue);
  }
}

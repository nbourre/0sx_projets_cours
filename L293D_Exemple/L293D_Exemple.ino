// Exemple de L293D

unsigned long currentTime = 0;

#define MOTOR_EN 2
#define MOTOR_INA 22
#define MOTOR_INB 23

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(MOTOR_EN, OUTPUT);
  pinMode(MOTOR_INA, OUTPUT);
  pinMode(MOTOR_INB, OUTPUT);

  digitalWrite(MOTOR_EN, 1);
  digitalWrite(MOTOR_INA, 1);
  digitalWrite(MOTOR_INB, 0);
}

void loop() {
  currentTime = millis();
  // put your main code here, to run repeatedly:
  
  Serial.println("Accélération");
  for (int i = 0; i < 256; i++) {
    analogWrite(MOTOR_EN, i);
    delay(10);
  }
  
  Serial.println("Décélération");
  for (int i = 255; i >= 0; i--) {
    analogWrite(MOTOR_EN, i);
    delay(10);
  }
}

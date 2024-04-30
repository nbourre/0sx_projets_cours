// Exemple de L293D

//               ________  ________
//              |        \/        |
// PIN2  EN1,2  | 1             16 | Vcc1 (Vss)
// PIN22 IN1    | 2             15 | IN4
// M+    OUT1   | 3             14 | OUT4
//       GND    | 4   L293D     13 | GND
//       GND    | 5             12 | GND
// M-    OUT2   | 6             11 | OUT3
// PIN23 IN2    | 7             10 | IN3
// Vcc   Vcc2   | 8              9 | EN3,4
//              |__________________|


unsigned long currentTime = 0;

#define MOTOR_EN 2
#define MOTOR_INA 22
#define MOTOR_INB 23

void setup() {
  Serial.begin(9600);
  
  pinMode(MOTOR_EN, OUTPUT);
  pinMode(MOTOR_INA, OUTPUT);
  pinMode(MOTOR_INB, OUTPUT);

  digitalWrite(MOTOR_EN, 1);
  digitalWrite(MOTOR_INA, 1);
  digitalWrite(MOTOR_INB, 0);
}

void loop() {
  currentTime = millis();
  
  
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

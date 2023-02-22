unsigned long currentTime = 0;

unsigned long serialPrintPrevious = 0;
int serialPrintInterval = 500;
String msg = "";

void setup() {
  Serial.begin(9600);

}

void loop() {
  currentTime = millis();
  
  int val = map(analogRead(A0), 0, 1023, 100, 0);
  
  Serial.println(val);
  delay(100);
  
}

void serialPrintTask() {
  if (currentTime - serialPrintPrevious < serialPrintInterval) return;

  serialPrintPrevious = currentTime;

  if (msg != "") {
    Serial.println(msg);
    msg = "";
  }

}
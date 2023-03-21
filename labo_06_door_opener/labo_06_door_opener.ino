#include "PorteGarage.h"

unsigned long currentTime = 0;

unsigned long serialPrintPrevious = 0;
int serialPrintInterval = 500;
String msg = "";

PorteGarage porte(2, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  // put your main code here, to run repeatedly:

}

void serialPrintTask() {
  if (currentTime - serialPrintPrevious < serialPrintInterval) return;

  serialPrintPrevious = currentTime;

  if (msg != "") {
    Serial.println(msg);
    msg = "";
  }

}
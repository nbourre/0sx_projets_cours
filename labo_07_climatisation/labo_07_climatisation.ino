#include "Climatisation.h"

unsigned long currentTime = 0;

unsigned long serialPrintPrevious = 0;
int serialPrintInterval = 500;
String msg = "";

Climatisation climatisation(8, 9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  // put your main code here, to run repeatedly:

  climatisation.update();

}
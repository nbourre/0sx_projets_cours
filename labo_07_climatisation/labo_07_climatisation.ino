#include "Climatisation.h"

unsigned long currentTime = 0;

Climatisation climatisation(8, 9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  // put your main code here, to run repeatedly:

  climatisation.update();

}
#include "Climatisation.h"

unsigned long currentTime = 0;


// Modifiez pour vos broches
Climatisation climatisation(8, 9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  

  climatisation.update();

}
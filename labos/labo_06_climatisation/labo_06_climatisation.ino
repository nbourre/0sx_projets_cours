#include "Climatisation.h"

unsigned long currentTime = 0;


// Adapter le code selon votre branchement
Climatisation climatisation(8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  

  climatisation.update();

}
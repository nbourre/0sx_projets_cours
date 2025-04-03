// Minimal test project to create a class
// that includes an encapsulated IR remote control
#include <IRremote.hpp>
#include "Climatisation.h"

Climatisation climatisation(&IrReceiver);
//Climatisation climatisation(&IrReceiver, 26);
//Climatisation climatisation(26);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  climatisation.setSerial(&Serial);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  climatisation.update();
}


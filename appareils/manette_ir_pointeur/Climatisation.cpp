// IMPORTANT!! Inclure IRremote.hpp avant les autres inclusions!
//#include <IRremote.hpp>
#include "Climatisation.h"

Climatisation::Climatisation(IRrecv *irrecv, int pinIR) : _pinIR(pinIR)
{
  _irrecv = irrecv;
  _irrecv->begin(_pinIR, ENABLE_LED_FEEDBACK);
}


Climatisation::Climatisation(int pinIR) : _pinIR(pinIR)
{
  _irrecv = &IrReceiver;
  _irrecv->begin(_pinIR, ENABLE_LED_FEEDBACK);
}

Climatisation::Climatisation(IRrecv *irrecv) {
  _irrecv = irrecv;
  _hasRemote = true;
  _irrecv->begin(26, ENABLE_LED_FEEDBACK);
}

void Climatisation::update() {

  if (_irrecv->decode()) {
    Serial.println(_irrecv->decodedIRData.protocol);
    Serial.println(_irrecv->decodedIRData.command);
    _irrecv->resume();
  }
}

// Testing purpose
void Climatisation::blinkTask() {
  static unsigned long lastTime = 0;
  const int rate = 250;

  if (millis() - lastTime < rate) return;

  lastTime = millis();

  int value = digitalRead(LED_BUILTIN) ? 0 : 1;
  digitalWrite(LED_BUILTIN, !value);
}
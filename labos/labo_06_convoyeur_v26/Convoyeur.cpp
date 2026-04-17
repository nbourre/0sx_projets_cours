#include "Convoyeur.h"

// Initialisation de l'instance static du Convoyeur
// Pour l'instant null
Convoyeur *Convoyeur::instance = nullptr;

// TODO : Compléter le constructeur
Convoyeur::Convoyeur(byte motPin1, byte motPin2, byte manette, byte btnPin, byte aff_CLK, byte aff_DIN, byte aff_CS)
  : _button (btnPin), _u8g2(U8G2_R0, aff_CLK, aff_DIN, aff_CS, U8X8_PIN_NONE)

 {
  _button.attachClick(buttonClick, this);
}


void Convoyeur::buttonClick(void* context) {
  Convoyeur *self = static_cast<Convoyeur*>(context);
  self->_buttonPressed = true;

}

void Convoyeur::longPress(void* context) {
  Convoyeur *self = static_cast<Convoyeur*>(context);
  self->_longPress = true;
}

void Convoyeur::update() {
  _currentTime = millis();

  switch (_state) {
    case ConvState::AVANCE:
      // avanceState()
      break;

  }
}

void Convoyeur::avanceState() {
  static unsigned long _lastTime = 0;

}
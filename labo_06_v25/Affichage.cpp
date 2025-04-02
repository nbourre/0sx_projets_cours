#include "Affichage.h"

// Constructeur avec initialisation de l'écran
Affichage::Affichage(int data_pin, int clk_pin, int cs_pin)
  : _u8g2(U8G2_R0, clk_pin, data_pin, cs_pin, U8X8_PIN_NONE, U8X8_PIN_NONE)
{
  _u8g2.begin();
  _u8g2.setFont(u8g2_font_4x6_tr); // Police adaptée pour un écran 8x8
}

// Met à jour l'affichage selon l'état courant
void Affichage::update() {
  _currentTime = millis();
  
  _u8g2.clearBuffer();

  switch (_currentState) {
    case EMPTY:
      // Ne rien afficher
      break;

    case ERROR:
      errorState();
      break;

    case BAD_COMMAND:
      badCommandState();
      break;
  }

  _u8g2.sendBuffer();
}

void Affichage::errorState() {
  static unsigned long lastTime = 0;
  static unsigned long exitTime = 0;
  const int rate = 100;

  static bool firstTime = true;

  if (firstTime) {
    exitTime = _currentTime + _timeout;

    firstTime = false;
    return;
  }

  // Ligne nécessaire si l'on doit temporiser
  // les appels de cet état
  if (_currentTime - lastTime < rate) return;

  lastTime = _currentTime;
  
  _u8g2.drawStr(0, 7, "E");  // Affiche 'E' pour Error

  bool transition = _currentTime > exitTime;


  if (transition) {
       
    firstTime = true;
    _currentState = EMPTY;
    
  }
}

void Affichage::badCommandState() {
  // TODO : À compléter
  _u8g2.drawStr(0, 7, "?");  // Affiche '?' pour commande invalide
  
}

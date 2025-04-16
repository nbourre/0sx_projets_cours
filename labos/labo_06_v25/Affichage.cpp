#include "Affichage.h"

// Constructeur avec initialisation de l'écran
Affichage::Affichage(int data_pin, int clk_pin, int cs_pin) {
  _u8g2 = new U8G2_MAX7219_8X8_F_4W_SW_SPI(U8G2_R0, clk_pin, data_pin, cs_pin, U8X8_PIN_NONE, U8X8_PIN_NONE);
}

void Affichage::init() {
  _u8g2->begin();
  _u8g2->setFont(u8g2_font_4x6_tr);
  _u8g2->setContrast(5);
}

// Met à jour l'affichage selon l'état courant
void Affichage::update() {
  _currentTime = millis();

  _u8g2->clearBuffer();

  switch (_currentState) {
    case EMPTY:
      // Ne rien afficher
      break;

    case MESSAGE:
      messageState();
      break;

    case ERROR:
      errorState();
      break;

    case BAD_COMMAND:
      badCommandState();
      break;
  }

  _u8g2->sendBuffer();
}

void Affichage::messageState() {
  static unsigned long lastTime = 0;
  static unsigned long exitTime = 0;
  const int rate = 150;  // Vitesse de défilement (ms)
  static bool firstTime = true;
  static int xOffset = 8;  // Position de départ (à droite de l’écran)

  if (firstTime) {
    exitTime = _currentTime + _timeout;
    xOffset = 8;  // Réinitialiser à droite
    firstTime = false;
    _resetTimeout = false;
    return;
  }

  if (_currentTime - lastTime < rate) return;
  lastTime = _currentTime;

  _u8g2->drawStr(xOffset, 7, _message);

  xOffset--;

  // Calcul de la largeur du texte
  int textWidth = _u8g2->getStrWidth(_message);

  if (_resetTimeout) {
    exitTime = _currentTime + _timeout;
    _resetTimeout = false;
  }

  // Transition message complété
  if (xOffset < -textWidth) {
    // Le texte a complètement défilé
    firstTime = true;
    _currentState = EMPTY;
  }

  // Transition 3 secondes
  // Timeout global (en cas de message plus long que prévu)
  if (_currentTime > exitTime) {
    firstTime = true;
    _currentState = EMPTY;
  }
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

  _u8g2->drawStr(0, 7, "E");  // Affiche 'E' pour Error

  bool transition = _currentTime > exitTime;


  if (transition) {

    firstTime = true;
    _currentState = EMPTY;
  }
}

void Affichage::badCommandState() {
  // TODO : À compléter
  _u8g2->drawStr(0, 7, "?");  // Affiche '?' pour commande invalide
}

void Affichage::setMessage(const char* msg) {
  // Copie sécuritaire du message dans le buffer local
  strncpy(_message, msg, MSG_SIZE - 1);
  _message[MSG_SIZE - 1] = '\0';  // S’assurer de la terminaison
  _currentState = MESSAGE;
  _resetTimeout = true;
}

const char* Affichage::getMessage() {
  return _message;
}

void Affichage::setMessageFromInt(int value) {
  char buffer[10];
  snprintf(buffer, sizeof(buffer), "%d", value);
  setMessage(buffer);  // Utilise ta méthode existante
  _currentState = MESSAGE;
  _resetTimeout = true;
}

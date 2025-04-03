#include "Climatisation.h"

// Constructeur
Climatisation::Climatisation(int pinMotorA, int pinMotorB, int pinLed, int pinDht) : _dht(pinDht, DHTTYPE){
  // Initialisation des attributs
  _pinMotorA = pinMotorA;
  _pinMotorB = pinMotorB;
  _pinLed = pinLed;
  _pinDht = pinDht;
  _onPause = false;
  _temperature = 0;
  _humidity = 0;
  _currentTime = 0;

  // TODO : Initialiser les pins

  // TODO : Initialiser le DHT
}

// Lecture du DHT à l'intervalle TEMP_INTERVAL
void Climatisation::readDht() {
    static unsigned long _dhtPrevious = 0;

    if (_currentTime - _dhtPrevious < TEMP_INTERVAL) return;

    _dhtPrevious = _currentTime;

    // TODO : Lire la température et l'humidité
}

// Méthode update
void Climatisation::update() {
  _currentTime = millis();

  // TODO : Faire la lecture

  switch (_motorState)
  {
    case ON:
        onState();
        break;
    case OFF:
        offState();
        break;
    case PAUSE:
        pauseState();
        break;
    default:
        break;
  }
}

// Méthode onState
void Climatisation::onState() {
    // TODO : Compléter la méthode
    
    // Avant de mettre le moteur et la DEL à ON
    // Vérifier si le moteur doit être sur pause
    // Vérifier la température pour mettre le moteur sur OFF
    // si la température est inférieure à _lowTemp

}

// Méthode offState
void Climatisation::offState() {
    // TODO : Compléter la méthode
    
    // Avant de mettre le moteur à off
    // Vérifier la température pour mettre le moteur sur ON
}

// Méthode pauseState
void Climatisation::pauseState() {
    // TODO : Compléter la méthode

    // Si le moteur n'est plus sur pause
    // mettre le moteur sur ON
}
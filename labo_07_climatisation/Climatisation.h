// Classe Climatisation
// gère un moteur DC branché un pin PWM et une DEL
// possède un DHT11 pour le contrôle de la température
// Tâche : Le moteur et la DEL s'active lorsque la température est supérieure à 23°C
// Tâche : Le moteur et la DEL s'arrête lorsque la température est inférieure à 22°C
// Tâche : Le moteur est sur Pause si la valeur de l'attribue onPause est à true

#ifndef CLIMATISATION_H
#define CLIMATISATION_H

#include <Arduino.h>
#include <DHT.h>

#define TEMP_INTERVAL 5000
#define DHTTYPE DHT11

// Énumération pour les états du moteur soit ON, OFF et PAUSE
enum MotorState { ON, OFF, PAUSE };


class Climatisation {
  public:
    // Constructeur
    Climatisation(int pinMotor, int pinLed, int pinDht);

    // Méthodes
    void update();
    void setOnPause(bool value) { _onPause = value; };
    bool getOnPause() { return _onPause; };

    // TODO : Ajouter les méthodes getTemperature et getHumidity
    // qui retourne la valeur des attributs _temperature et _humidity

    // TODO : Ajouter les méthodes setLowTemp et setHighTemp
    // pour ajuster la valeur des attributs _lowTemp et _highTemp

private:
    int _pinMotor;
    int _pinLed;
    int _pinDht;
    DHT _dht;

    bool _onPause;
    float _temperature;
    float _humidity;
    unsigned long _currentTime;
    int _lowTemp = 22;
    int _highTemp = 23;

    MotorState _motorState = OFF;

    void onState();
    void offState();
    void pauseState();

    void readDht();
};

#endif
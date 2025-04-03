// Classe cliente de la librairie IRremote.hpp
// qui inclut une télécommande IR encaspulée

#ifndef _CLIMATISATION_H_
#define _CLIMATISATION_H_

#define USE_IRREMOTE_HPP_AS_PLAIN_INCLUDE
#include <IRremote.hpp>

#include <Arduino.h>
#include <DHT.h>


class Climatisation {
public:
  // Constructeur
  Climatisation(IRrecv *irrecv);
  Climatisation(IRrecv *irrecv, int pinIR);
  Climatisation(int pinIR);

  // Méthodes
  void update();
  void setSerial(Print *aSerial) {serial = aSerial;};

private:
  IRrecv * _irrecv;
  int _pinIR;
  bool _hasRemote = false;
  Print *serial;
  
  void blinkTask();
};

#endif
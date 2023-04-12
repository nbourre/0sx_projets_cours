#pragma once

class Eclairage{
  public:
    // Constructeur
    Eclairage(int lumSensorPin, int ledPin);

    int getLuminosity() { return _lumValue; }
    int getMinLuminosity() { return _lumMin; }
    int getMaxLuminosity() { return _lumMax; }
    void setThreshold(int threshold);
    int getThreshold() { return _threshold; }

    // Fonction appelée dans le loop
    void update();

  private:
    int _lumSensorPin;
    int _ledPin;
    int _lumValue;
    int _lumMin;
    int _lumMax;
    int _threshold;
};

// Peut être déplacé dans le fichier Eclairage.cpp
Eclairage::Eclairage(int lumSensorPin, int ledPin){
  _lumSensorPin = lumSensorPin;
  _ledPin = ledPin;
  _lumMin = 1023;
  _lumMax = 0;
  _threshold = 30;
  pinMode(_ledPin, OUTPUT);
}

void Eclairage::update(){
  _lumValue = analogRead(_lumSensorPin);
  if (_lumValue > _lumMax ){
    _lumMax = _lumValue;
  }
  if (_lumValue < _lumMin){
    _lumMin = _lumValue;
  }
  int luminosity = map(_lumValue, _lumMin, _lumMax, 0, 100);
  if (luminosity < _threshold){
    digitalWrite(_ledPin,HIGH);
  }else{
    digitalWrite(_ledPin,LOW);
  }
}
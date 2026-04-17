#pragma once

// Mettre l'enum avant les includes
// Utiliser comme ceci ConvState::MARCHE, ConvState::ARRET...
enum class ConvState {MANUEL, CONSTANT, ACTIF, INACTIF};

#include <OneButton.h>
#include <U8g2lib.h>
  

class Convoyeur {
public:
  
  Convoyeur (byte motPin1, byte motPin2, byte manette, byte btnPin, byte aff_CLK, byte aff_DIN, byte aff_CS);

  // Retourne vrai si le moteur est en fonction
  bool estEnFonction();

  // Met à jour les états du convoyeur
  void update();

private:
  unsigned long _currentTime = 0;

  byte _moteur_pin_1 = 0;
  byte _moteur_pin_2 = 0;
  byte _manette = 0;
  byte _btn_pin = 0;
  byte _aff_CLK = 0;
  byte _aff_DIN = 0;
  byte _aff_CS = 0;

  // À ajuster selon les besoins du joystick
  // TODO : À rechercher sur Google
  int _joystickDeadZone = 5;

  OneButton _button;
  bool _buttonPressed = false;
  bool _longPress = false;

  static Convoyeur *instance;
  static void buttonClick(void *context);
  static void longPress(void *context);

  ConvState _state = ConvState::INACTIF;

  U8G2_MAX7219_8X8_F_4W_SW_SPI _u8g2;
  
  void manuelState();
  void constantState();
  void actifState();
  void inactifState();

  // Configure les broches du moteur
  void setMoteurVitesse(int vitesse);

  // Configure l'affichage du convoyeur
  void setAffichage(int id_symbole);
  
};
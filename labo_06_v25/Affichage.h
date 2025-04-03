#pragma once

#include <U8g2lib.h>

class Affichage {
public:
  enum State {EMPTY, ERROR, BAD_COMMAND};
  
  Affichage (int data_pin, int clk_pin, int cs_pin);
  
  void setState (State newState) {_currentState = newState; }
  State getState() { return _currentState; }
  
  void setTimeout(unsigned long timeout) {_timeout = timeout;}
  void getTimeout() {return _timeout; }
  
  void update();

private:
  State _currentState = EMPTY;
  
  unsigned long _currentTime = 0;
  unsigned long _timeout = 3000; // Temps d'affichage pour les états temporaires
  
  U8G2_MAX7219_8X8_F_4W_SW_SPI _u8g2;
  
  void errorState();
  void badCommandState();
  
};

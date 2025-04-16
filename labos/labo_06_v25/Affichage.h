#pragma once

#include <U8g2lib.h>

#define MSG_SIZE 64

class Affichage {
public:
  enum State {EMPTY, ERROR, BAD_COMMAND, MESSAGE, IDLE};
  
  Affichage (int data_pin, int clk_pin, int cs_pin);
  
  void setState (State newState) {_currentState = newState; }
  State getState() { return _currentState; }
  
  void setTimeout(unsigned long timeout) {_timeout = timeout;}
  void getTimeout() {return _timeout; }

  void setMessage(const char* msg);
  const char* getMessage();
  void setMessageFromInt(int value);
    
  void update();
  void init();
  U8G2* getU8G2() { return _u8g2; }


private:
  State _currentState = EMPTY;
  
  unsigned long _currentTime = 0;
  unsigned long _timeout = 3000; // Temps d'affichage pour les états temporaires
  bool _resetTimeout = false;
  char _message[MSG_SIZE] = "";
  
  U8G2_MAX7219_8X8_F_4W_SW_SPI*  _u8g2 = nullptr;
  
  void errorState();
  void badCommandState();
  void messageState();
  void idleState();
  
};

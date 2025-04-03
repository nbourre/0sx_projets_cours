#pragma once
#include <OneButton.h>

class Motor {
public:
  enum State { OFF,
               RUN_ENTER,
               ON,
               RUN_EXIT };

  Motor(int motorPin, int ledPin, int buttonPin);

  void update();

private:
  const int _motorPin;
  const int _ledPin;
  unsigned long _previousTime = 0;
  unsigned long _currentTime = 0;
  
  const int _blinkRate = 50;
  
  bool _buttonPressed = false;
  State _state = OFF;

  OneButton _button;

  static Motor *instance;
  static void buttonClick(Motor *self);
  static void buttonLongPress(Motor *self);

  bool timeElapsed(unsigned long duration);
  
  void offExecute();
  void runEnter();
  void runExit();
  void runExecute();
};

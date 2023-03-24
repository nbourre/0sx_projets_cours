#include "Motor.h"

// Initialisation de l'instance static du moteur
// Pour l'instant null
Motor *Motor::instance = nullptr;

// Constructeur
Motor::Motor(int motorPin, int ledPin, int buttonPin)
  : _motorPin(motorPin), _ledPin(ledPin) {
  pinMode(_motorPin, OUTPUT);
  pinMode(_ledPin, OUTPUT);

  instance = this;

  _button.setDebounceTicks(50);
  _button.setClickTicks(10);
  _button.setPressTicks(1000);

  _button.attachClick(buttonClick, instance);
  _button.attachLongPressStop(buttonLongPress, instance);
}

static void Motor::buttonClick(Motor *self) {
  self->_buttonPressed = true;
  self->_previousTime = millis();
  self->_state = RUN_ENTER;
}

static void Motor::buttonLongPress(Motor *self) {
  self->_buttonPressed = true;
  self->_state = RUN_EXIT;
  self->_previousTime = millis();
}

void Motor::offExecute() {
  digitalWrite(_motorPin, LOW);
  digitalWrite(_ledPin, LOW);
}

void Motor::runEnter() {
  static unsigned long lastTime = 0;
  
  if (timeElapsed(500)) {
    _state = ON;
    digitalWrite(_ledPin, HIGH);
  }
  
  if (_currentTime - lastTime >= _blinkRate) {
    lastTime = _currentTime;
    digitalWrite(_ledPin, !digitalRead(_ledPin));
  }
}

void Motor::runExecute() {
  digitalWrite(_motorPin, HIGH);
  digitalWrite(_ledPin, HIGH);
}

void Motor::runExit() {
  static unsigned long lastTime = 0;
  static int brightness = 255;
  
  if (timeElapsed(1000)) {
    _state = OFF;
    digitalWrite(_ledPin, LOW);
  }
  
  if (_currentTime - lastTime >= 4) {
    lastTime = _currentTime;
    
    brightness = brightness > 0 ? brightness - 1 : 0;
  }
  analogWrite(_ledPin, brightness);
}

void Motor::update() {
  _currentTime = millis();
  
  switch (_state) {
    case OFF:
      offExecute();
      break;
    case RUN_ENTER:
      runEnter();
      break;
    case ON:
      runExecute();
      break;
    case RUN_EXIT:
      runExit();
      break;
  }
}

bool Motor::timeElapsed(unsigned long duration) {
  if (millis() - _previousTime >= duration) {
    _previousTime = millis();
    return true;
  } else {
    return false;
  }
}
#include "LCD_I2C_Extended.h"

void LCD_I2C_Extended::update(){
  static unsigned long lastTime = 0;
  
  currentTime = millis();
  
  if (currentTime - lastTime < _interval) return;
  
  if (_callbacks.isEmpty()) return;
  
  lastTime = currentTime;
  
  Serial.print(_callbacks.getValue(_currentIdx++)());
  
  _currentIdx = _currentIdx > _callbacks.getSize() - 1 ? 0 : _currentIdx;
  
}
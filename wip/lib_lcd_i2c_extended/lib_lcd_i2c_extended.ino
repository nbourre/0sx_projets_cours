#include "LCD_I2C_Extended.h"

LCD_I2C_Extended lcd (0x27, 16, 2);

char * testCallbacks() {
  return "Potatoes!";
}

char * testCallbacks2() {
  return "Apple!";
}

void setup() {
  Serial.begin(9600);
  //lcd.init();
  lcd.addCallback(testCallbacks);
  lcd.addCallback(testCallbacks2);  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  lcd.update();
}

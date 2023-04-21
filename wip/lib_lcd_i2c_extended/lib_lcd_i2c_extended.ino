#include "LCD_I2C_Extended.h"

LCD_I2C_Extended lcd (0x27, 16, 2);

char * testCallbacks() {
  return "Potatoes!";
}

char * testCallbacks2() {
  return "Apple!";
}

char * testStringCb() {
  static String result = "Mucho potatoes!";
  static char _buff[20] = "";
  result.toCharArray(_buff, result.length());
  
  return _buff;
}

void setup() {
  Serial.begin(9600);
  //lcd.init();
  lcd.addCallback(testCallbacks);
  lcd.addCallback(testCallbacks2);  
  lcd.addCallback(testStringCb);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  lcd.update();
}

#include <Arduino.h>
#include "Eclairage.h"
#include "Affichage.h"
#include "HCSR04.h"

#define LED_PIN 4
#define LUM_SENSOR_PIN A0
#define ECHO_PIN 2
#define TRIGGER_PIN 3
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

Eclairage eclairage(LUM_SENSOR_PIN, LED_PIN);
HCSR04 hc(ECHO_PIN, TRIGGER_PIN);
Affichage affichage(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

unsigned long currentTime;

void setup() {
  Serial.begin(9600);  
}

void loop() {
  currentTime = millis();

  eclairage.update();

  affichage.setLine1("Distance: " + String(hc.dist()));
  affichage.setLine2("Luminosite: " + String(eclairage.getLuminosity()));
  affichage.update();
}
#include <Arduino.h>
#include <U8g2lib.h>
#include <avr/pgmspace.h>

class Matrice8x8 {
public:
  Matrice8x8(uint8_t clk, uint8_t din, uint8_t cs)
    : _u8g2(U8G2_R0, clk, din, cs, U8X8_PIN_NONE, U8X8_PIN_NONE) {
  }

  void begin() {
    _u8g2.begin();
  }

  void afficherSmiley() {
    _u8g2.clearBuffer();
    _u8g2.drawXBMP(0, 0, 8, 8, bitmapSmiley);
    _u8g2.sendBuffer();
  }

  void afficherCoeur() {
    _u8g2.clearBuffer();
    _u8g2.drawXBMP(0, 0, 8, 8, bitmapCoeur);
    _u8g2.sendBuffer();
  }

  void afficherFleche() {
    _u8g2.clearBuffer();
    _u8g2.drawXBMP(0, 0, 8, 8, bitmapFleche);
    _u8g2.sendBuffer();
  }

private:
  U8G2_MAX7219_8X8_F_4W_SW_SPI _u8g2;

  // Déclaration (dans la classe)
  static const uint8_t bitmapSmiley[];
  static const uint8_t bitmapCoeur[];
  static const uint8_t bitmapFleche[];
};

// Définition (hors classe) avec PROGMEM
const uint8_t Matrice8x8::bitmapSmiley[] PROGMEM = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

const uint8_t Matrice8x8::bitmapCoeur[] PROGMEM = {
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

const uint8_t Matrice8x8::bitmapFleche[] PROGMEM = {
  B00011000,
  B00011100,
  B11111110,
  B11111111,
  B11111110,
  B00011100,
  B00011000,
  B00000000
};

// Utilisation
Matrice8x8 matrice(13, 11, 10);

void setup() {
  matrice.begin();

  matrice.afficherSmiley();
  delay(1000);

  matrice.afficherCoeur();
  delay(1000);

  matrice.afficherFleche();
}

void loop() {
}
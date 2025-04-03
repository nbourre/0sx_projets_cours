/*
   Exemple d'affichage séquentiel de différentes fonctions de tracé
   sur une matrice 8×8 avec MAX7219, via la librairie U8g2.

   Matériel :
     - MAX7219 (1 module 8×8)
     - Arduino (UNO, Mega, etc.)
     - Brancher en mode SPI logiciel :
         CLK_PIN -> CLK
         DIN_PIN -> DIN
         CS_PIN  -> CS (LOAD)
*/

#include <Arduino.h>
#include <U8g2lib.h>

// Broches pour SPI logiciel (à ajuster selon votre circuit)
#define CLK_PIN  30
#define DIN_PIN  34
#define CS_PIN   32

// Création de l'objet U8g2 pour un module 8×8 MAX7219
U8G2_MAX7219_8X8_F_4W_SW_SPI u8g2(
  U8G2_R0,  // Rotation
  CLK_PIN,  // clock
  DIN_PIN,  // data
  CS_PIN,   // cs
  U8X8_PIN_NONE, // dc
  U8X8_PIN_NONE  // reset
);

// Variables pour gérer le basculement de mode toutes les secondes
uint8_t appState = 0;            // Mode actuel (0 à 5)
unsigned long prevModeTime;  // Pour se souvenir du temps précédent

// Pour l'animation du pixel itinérant (mode 0)
uint8_t pixelX = 0;
uint8_t pixelY = 0;
bool goingRight = true;
bool goingDown = true;

// Délai d'animation du pixel en ms
const unsigned long moveInterval = 100; 
// Délai de changement de mode en ms
const unsigned long modeInterval = 1000;

// --------------------------------------------------------------
// setup()
// --------------------------------------------------------------
void setup() {
  u8g2.begin();
  // Sur un MAX7219, la plage de luminosité est environ 0..15 (selon la version)
  // On peut mettre setContrast(15) pour plus brillant
  u8g2.setContrast(10);
  
  // Petit délai initial pour la stabilisation
  delay(500);

  prevModeTime = millis();
}

// --------------------------------------------------------------
// Fonction : demoPixelScan
//   Mode 0 : un pixel bouge dans l'écran, rebondit sur les bords
// --------------------------------------------------------------
void demoPixelScan() {
  static unsigned long lastTime = millis();
      
  // Gérer l'animation : tous les moveInterval ms
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= moveInterval) {
    lastTime = currentTime;
    
    // Mise à jour de pixelX
    if (goingRight) {
      if (pixelX < 7) pixelX++;
      else goingRight = false;
    } else {
      if (pixelX > 0) pixelX--;
      else goingRight = true;
    }

    // Mise à jour de pixelY
    if (goingDown) {
      if (pixelY < 7) pixelY++;
      else goingDown = false;
    } else {
      if (pixelY > 0) pixelY--;
      else goingDown = true;
    }
  }
  
  // Dessin du pixel
  u8g2.drawPixel(pixelX, pixelY);
}

// --------------------------------------------------------------
// Fonction : demoHLineVLine
//   Mode 1 : trace 2 lignes horizontales et 2 lignes verticales
// --------------------------------------------------------------
void demoHLineVLine() {
  // Lignes horizontales
  //  - y=0, de x=0 à x=7
  //  - y=7, de x=0 à x=7
  u8g2.drawHLine(0, 0, 8);
  u8g2.drawHLine(0, 7, 8);

  // Lignes verticales
  //  - x=0, de y=0 à y=7
  //  - x=7, de y=0 à y=7
  u8g2.drawVLine(0, 0, 8);
  u8g2.drawVLine(7, 0, 8);
}

// --------------------------------------------------------------
// Fonction : demoLine
//   Mode 2 : trace une ligne diagonale
// --------------------------------------------------------------
void demoLine() {
  // On dessine une ligne de (0,0) à (7,7)
  u8g2.drawLine(0, 0, 7, 7);
}

// --------------------------------------------------------------
// Fonction : demoBox
//   Mode 3 : dessine un petit carré (4×4) centré
// --------------------------------------------------------------
void demoBox() {
  // Sur 8×8, on peut dessiner un box 4×4 au milieu
  // On le place grosso modo au centre
  //  => coin supérieur gauche vers (2,2)
  //  => 4 pixels de large, 4 pixels de haut
  u8g2.drawBox(2, 2, 4, 4);
}

// --------------------------------------------------------------
// Fonction : demoCircle
//   Mode 4 : dessine un cercle. Sur 8×8, c'est minuscule!
// --------------------------------------------------------------
void demoCircle() {
  // Dessin d'un petit cercle de rayon 3 centré en (4,4)
  // Note : Y=4, X=4 => c'est environ le centre
  // Sur 8×8, on fait ce qu'on peut ;)
  u8g2.drawCircle(4, 4, 3, U8G2_DRAW_ALL);
}

// --------------------------------------------------------------
// Fonction : demoTriangle
//   Mode 5 : dessine un triangle
// --------------------------------------------------------------
void demoTriangle() {
  // Bizarrement, il faut mettre -1 à y
  // ça doit être un truc d'arrondi
  u8g2.drawTriangle(3, -1, 7, 8, 0, 6);
}

// --------------------------------------------------------------
// loop()
//   À chaque itération :
//
//   1) Tous les modeInterval ms, on passe au mode suivant
//   2) On efface, on dessine selon le mode, on envoie
// --------------------------------------------------------------
void loop() {
  unsigned long currentTime = millis();

  // Gérer le changement de mode toutes les secondes
  if (currentTime - prevModeTime >= modeInterval) {
    prevModeTime = currentTime;
    appState++;
    if (appState > 5) appState = 0;
    
    // Réinitialiser le pixel pour le mode 0
    if (appState == 0) {
      pixelX = 0;
      pixelY = 0;
      goingRight = true;
      goingDown = true;
    }
  }

  // Effacer le buffer avant de dessiner
  u8g2.clearBuffer();

  // Dessiner selon le mode
  switch (appState) {
    case 0: // Pixel itinérant
      demoPixelScan();
      break;
    case 1: // Lignes horizontales & verticales
      demoHLineVLine();
      break;
    case 2: // drawLine
      demoLine();
      break;
    case 3: // drawBox
      demoBox();
      break;
    case 4: // drawCircle
      demoCircle();
      break;
    case 5: // drawTriangle
      demoTriangle();
      break;
  }

  // Envoyer l'image à l'afficheur
  u8g2.sendBuffer();

  // Petit délai d'itération
  delay(50);
}

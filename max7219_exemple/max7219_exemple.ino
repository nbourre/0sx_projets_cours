/*
  Basé sur : https://github.com/olikraus/u8g2/blob/master/sys/arduino/u8g2_full_buffer/MAX7219_Scroll/MAX7219_Scroll.ino
  Exemple d'affichage défilant sur une matrice LED 8x8 contrôlée par un MAX7219
*/

#include <Arduino.h>
#include <U8g2lib.h>

// Définition des broches utilisées pour la communication SPI logicielle
#define CLK_PIN 30
#define DIN_PIN 34
#define CS_PIN  32  // Chip Select

// Définir le nombre de matrices chaînées (1 ou plus)
#define NOMBRE_MATRICES 1  // <-- Change ça selon ton montage
#define LARGEUR_POLICE 4 // Adapter pour la dimension de la police

// Initialisation de l'afficheur MAX7219 8x8 via SPI logiciel
U8G2_MAX7219_8X8_F_4W_SW_SPI display(U8G2_R0, /* clock=*/ CLK_PIN, /* data=*/ DIN_PIN, /* cs=*/ CS_PIN, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);

// Variables pour contrôler le défilement du texte
uint16_t position_bits = 0;  // Position actuelle du texte en bits
uint16_t longueur_bits;      // Longueur totale du texte en bits

// Texte à faire défiler sur l'afficheur
char *message = "    Salut de U8g2... Librairie Graphique pour Arduino    ";

// Largeur visible en pixels = nombre de matrices * 8
const uint8_t largeur_affichage = NOMBRE_MATRICES * 8;

void setup(void) {
  display.begin();                             // Initialiser l'afficheur
  
  display.setFont(u8g2_font_4x6_tr); // Choisir une police lisible
  display.setDisplayRotation(U8G2_R0);             // Assurer l’orientation par défaut
  display.setContrast(5); // Permet d'ajuster la luminosité (contraste) de l'affichage
  
  position_bits = 0;
  longueur_bits = strlen(message) * LARGEUR_POLICE + largeur_affichage;           // Calculer la longueur du texte en pixels (8 bits par caractère)
  
  display.clearBuffer();
  display.drawLine(0, 0, 7, 7);
  display.sendBuffer();
  delay(500);
  
  display.clearBuffer();
  display.drawLine(7, 0, 0, 7);
  display.sendBuffer();
  delay(500);
}

#define TAILLE_TAMPON 12

// Fonction pour dessiner une portion du texte à une position donnée (en bits)
void dessiner_message_a_position(const char *texte, uint16_t position_bits)
{
  char tampon[TAILLE_TAMPON];               // Tampon pour contenir une portion du texte
  uint16_t debut_caractere = position_bits / LARGEUR_POLICE; // Index du caractère de départ
  uint16_t i;

  // Copier une portion du texte dans le tampon
  for (i = 0; i < TAILLE_TAMPON - 1; i++) {
    tampon[i] = texte[debut_caractere + i];
    if (texte[debut_caractere + i] == '\0')
      break;
  }

  tampon[TAILLE_TAMPON - 1] = '\0'; // S'assurer que le tampon est bien terminé

  // Afficher le texte en tenant compte du décalage de bits (scroll horizontal)
  display.drawStr(-(position_bits & (LARGEUR_POLICE - 1)), 7, tampon);
}

void loop(void) {
  display.clearBuffer();                               // Effacer le contenu du tampon interne de l'afficheur
  dessiner_message_a_position(message, position_bits);   // Afficher une portion du texte à la bonne position
  display.sendBuffer();                                // Envoyer le tampon à l'afficheur physique
  
  position_bits++;                                       // Avancer d'un pixel
  
  if (position_bits >= longueur_bits) {
    position_bits = 0;                                   // Recommencer à zéro quand le texte a entièrement défilé
  }
  
  delay(60);                                             // Petite pause pour ralentir le défilement
}

#include "Climatisation.h"
#include "PorteGarage.h"

unsigned long currentTime = 0;

Climatisation climatisation(8, 9, 10);

PorteGarage porte(2, 7, 5, 6, 4);

void eventMoteur(bool valeur, String quoi) {
  Serial.print (quoi);
  Serial.print (" -- Mouvement : ");
  Serial.println (valeur);
  
  // TODO
  // On pourrait par exemple, mettre en pause
  // un autre moteur pour éviter la surchage ;)
}

void setup() {
  Serial.begin(9600);
  porte.setCallBack(eventMoteur);
}

void loop() {
  currentTime = millis();
  // put your main code here, to run repeatedly:

  porte.update();
  climatisation.update();

}
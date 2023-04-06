#include "PorteGarage.h"

unsigned long currentTime = 0;

unsigned long serialPrintPrevious = 0;
int serialPrintInterval = 500;
String msg = "";

PorteGarage porte(2, 8, 10, 9, 11);

void eventMoteur(bool valeur, String quoi) {
  Serial.print (quoi);
  Serial.print (" -- Mouvement : ");
  Serial.println (valeur);
  
  // On pourrait par exemple, mettre en pause
  // un autre moteur pour éviter la surchage ;)
}

void setup() {
  Serial.begin(9600);
  
  // Quand le moteur va changer d'état (on ou off)
  // il va appeler cette méthode
  porte.setCallBack(eventMoteur);
}

void loop() {
  currentTime = millis();
  // put your main code here, to run repeatedly:

  porte.update();
}

void serialPrintTask() {
  if (currentTime - serialPrintPrevious < serialPrintInterval) return;

  serialPrintPrevious = currentTime;

  if (msg != "") {
    Serial.println(msg);
    msg = "";
  }

}
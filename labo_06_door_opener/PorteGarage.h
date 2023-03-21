#pragma once
#include <Arduino.h>
#include <AccelStepper.h>
#include <OneButton.h>


class PorteGarage {
  public:
    enum Etat { 
      CALIB, // État de calibration
      OUVERT,
      OUVERTURE,
      FERME,
      FERMETURE,
      ARRET
    };

    PorteGarage(int pinButton) : btn (pinButton) {
      etat = CALIB;
      instance = this;
      btn.attachClick(buttonClick, instance);
    };

    void ouvrir();
    void fermer();
    void calibrer();
    Etat getEtat();
    static void buttonClick(PorteGarage *self);

    void update();
    

  private:
    Etat etat;
    OneButton btn;
    static PorteGarage *instance;
    
    void ouvrirEnter();
    void ouvrirExit();
    
    void fermerEnter();
    void fermerExit();
        
};

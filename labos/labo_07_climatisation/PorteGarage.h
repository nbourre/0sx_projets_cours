#include "pins_arduino.h"
#pragma once
#include <Arduino.h>
#include <AccelStepper.h>
#include <OneButton.h>


class PorteGarage {
  public:
    enum Etat { 
      NOT_INIT, // Non initialise 
      CALIB, // État de calibration
      OUVERT,
      OUVERTURE,
      FERME,
      FERMETURE,
      ARRET
    };

    /*!
      @brief Constructeur qui permet d'initialiser les différents broches de la porte de garage.
      @param  pinButon
              Numéro de la broche du bouton
      @param  step_pin1..4
              Numéro des broches du stepper motor
    */
    PorteGarage(int pinButton, uint8_t step_pin1, uint8_t step_pin2, uint8_t step_pin3, uint8_t step_pin4) :
                   btn (pinButton), 
                   stepper(AccelStepper::FULL4WIRE, step_pin1, step_pin2, step_pin3, step_pin4) {
      etat = NOT_INIT;
      instance = this;
      btn.attachClick(buttonClick, instance);
      btn.attachLongPressStart(buttonLongPress, instance);
      callback = NULL;

      pinMode (LED_BUILTIN, OUTPUT);
      stepper.setMaxSpeed(maxSpeed);
      stepper.setAcceleration(maxAccel);
    };
    
    Etat getEtat() { return etat; };

    void update();
    
    void printStatus();
    
    // Méthode pour définir le callback (pointeur de fonction) lorsque l'état de la porte de garage change
    // En bref, c'est pour déclencher un événement
    // state 0 --> ne bouge plus
    // state 1 --> en mouvement
    PorteGarage &setCallBack(void (*callback)(bool moving, String)) {
      this->callback = callback;
      return *this;
    }

  private:
    Etat etat;
    Etat previousState;
    OneButton btn;
    AccelStepper stepper;
    static PorteGarage *instance;
    
    // Nombre de pas pour un cycle ouvrir/fermer
    const int nbPasCycle = 2038;
    const int maxSpeed = 500;
    const int maxAccel = 500;
    
    unsigned long currentTime = 0;
    
    bool debug = false;
    
    void ouvrir();
    void fermer();
    void calibrer();
    static void buttonClick(PorteGarage *self);
    static void buttonLongPress(PorteGarage *self);
    void attente();
    void arret();
    
    void ouvrirEnter();    
    void fermerEnter();
    void calibrerEnter();
    void calibrerExit();
    
    void (*callback)(bool, String);
    
    void sendEvent(bool);
    
    void blinkTask();
    
    
        
};

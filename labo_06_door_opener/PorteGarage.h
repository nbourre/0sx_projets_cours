/*!
 * @file PorteGarage.h
 *
 *
 */

#pragma once
#include <Arduino.h>
#include <AccelStepper.h>
#include <OneButton.h>

/*! 
    @brief  Classe qui contrôle un ouvre-porte de garage à l'aide d'un moteur pas-à-pas 28byj-48 et d'un bouton
*/
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
    };

    void ouvrir();
    void fermer();
    void calibrer();
    Etat getEtat() { return etat; };

    void update();
    
    // Ajouter les méthodes manquantes si nécessaires

  private:
    Etat etat;
    AccelStepper stepper;
    OneButton btn;
    
    static PorteGarage *instance;
    
    static void buttonClick(PorteGarage *self);
        
    void calibrerEnter();
    void calibrerExit();
    
    void ouvrirEnter();
    void ouvrirExit();
    
    void fermerEnter();
    void fermerExit();
    
    // Ajouter les méthodes manquantes si nécessaires
        
};

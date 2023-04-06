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
      callback = NULL;

      // Attention! Le stepper n'est pas configuré. Il faut compléter le code
      // TODO : Complétez le constructeur     
    };


    Etat getEtat() { return etat; };

    void update();
    
    // Méthode pour définir le callback (pointeur de fonction) lorsque l'état de la porte de garage change
    // En bref, c'est pour déclancher un événement
    // state 0 --> ne bouge plus
    // state 1 --> en mouvement
    
    PorteGarage &setCallBack(void (*callback)(bool moving, String)) {
      this->callback = callback;
      return *this;
    }

    // Ajouter les méthodes manquantes si nécessaires

  private:
    Etat etat;
    AccelStepper stepper;
    OneButton btn;

    const int troisTours = 3 * 2038;
    
    static PorteGarage *instance;
    
    void ouvrir();
    void fermer();
    void calibrer();
    void attente();
    
    static void buttonClick(PorteGarage *self);
        
    void calibrerEnter();
    
    void ouvrirEnter();
    
    void fermerEnter();

    void (*callback)(bool, String);
    
    void sendEvent(bool);

    // Ajouter les méthodes manquantes si nécessaires
        
};

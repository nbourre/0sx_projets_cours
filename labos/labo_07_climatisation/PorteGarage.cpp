#include "PorteGarage.h"

PorteGarage* PorteGarage::instance = nullptr;

static void PorteGarage::buttonLongPress(PorteGarage *self) {
  self->etat = NOT_INIT;
  self->stepper.stop();
  self->sendEvent(false);
  
  Serial.println("Appuyer pour lancer la calibration");
  
  if (self->debug) {
    Serial.print ("Long press detected.\tCurrent State : ");
    Serial.println (self->getEtat());
  }
}

static void PorteGarage::buttonClick(PorteGarage *self) {
  
  // Faire le code de gestion du clic
  // Pour utiliser les méthodes et attributs d'un
  // pointeur, il faut utiliser la notation "->".
  // Exemple : self->etat // pour utiliser etat d'un pointeur.
  
  switch (self->etat) {
    case OUVERT:
      self->fermerEnter();
      break;
    case FERME:
      self->ouvrirEnter();
      break;
    case OUVERTURE:
    case FERMETURE:
      
      self->arret();
      break;
    case ARRET:
      if (self->previousState == OUVERTURE) {
        self->fermerEnter();
      } else {
        self->ouvrirEnter();
      }
      break;
    case NOT_INIT:
      self->calibrerEnter();
      break;
    case CALIB:
      self->calibrerExit();
      break;
    default:
      break;
  }
  
  if (self->debug) {
    Serial.print ("Click detected.\tCurrent State : ");
    Serial.println (self->getEtat());
  }
};

// Ouverture de la porte
void PorteGarage::ouvrir() {
  // Implémentation de la méthode ouvrir()
  
  if (stepper.distanceToGo() == 0) {
    etat = OUVERT;
    
    sendEvent(false);
    Serial.println("Ouvert");
  }
}

// Préparation à l'ouverture
void PorteGarage::ouvrirEnter() {
  // Faire les initialisations et instructions
  // nécessaires pour faire l'ouverture;
  Serial.println("Ouverture");
  stepper.moveTo(0);
  etat = OUVERTURE;
  
  sendEvent(true);
}

// Fermeture de la porte
void PorteGarage::fermer() {
  // Implémentation de la méthode fermer()
  // Effectuer les 3 tours pour fermer la porte
  // Lorsque ce sera fait, changer l'état de la porte

  if (stepper.distanceToGo() == 0) {
    etat = FERME;
    
    sendEvent(false);
    Serial.println("Fermer");
  }
}


// Préparation à la fermeture
void PorteGarage::fermerEnter() {
  Serial.println("Fermeture");
  
  stepper.moveTo(-nbPasCycle);
  etat = FERMETURE;
  
  sendEvent(true);
}

void PorteGarage::calibrerEnter() {
  Serial.println("Calibration");
  stepper.setSpeed(maxSpeed);
  stepper.moveTo(10 * nbPasCycle);
  etat = CALIB;
  sendEvent(true);  
}

// Calibration de la porte
void PorteGarage::calibrer() {
  if (stepper.distanceToGo() == 0) {
    etat = OUVERT;
    
    sendEvent(false);
  }
}

void PorteGarage::calibrerExit() {
    stepper.setCurrentPosition(0);
    etat = OUVERT;
    sendEvent(false);
}

// Attente d'un événement
// Il se peut qu'il n'y ait rien à faire dans cette méthode
void PorteGarage::attente() {
  // Ajouter des trucs si nécessaire
}

void PorteGarage::arret() {
  previousState = etat;
  etat = ARRET;
  
  stepper.stop();
  sendEvent(false);
  
  Serial.print(previousState == FERMETURE ? "Fermeture" : "Ouverture");
  Serial.println(" --> Arret");
  
}

// Permet d'appeler la méthode de rappel si elle est présente
void PorteGarage::sendEvent(bool moving) {
  if (callback) {
    callback(moving, "Garage");
  }
}

void PorteGarage::blinkTask() {
  static unsigned long lastTime = 0;
  static int ledState = LOW;
  const int blinkRate = 100;
  
  if (!stepper.isRunning()) {
    digitalWrite(LED_BUILTIN, LOW);
    return;
  }
  
  if (currentTime - lastTime >= blinkRate) {
    lastTime = currentTime;
    
    ledState = !ledState;
    
    digitalWrite(LED_BUILTIN, ledState);
  }
}

void PorteGarage::update() {
  currentTime = millis();

  switch (etat) {
    case OUVERT:
    case FERME:
    case NOT_INIT:
    case ARRET:
      attente();
      break;
    case OUVERTURE:
      ouvrir();
      break;
    case FERMETURE:
      fermer();
      break;
    case CALIB:
      calibrer();
      break;
    default:
      break;
  }
  
  blinkTask();
  
  // Met à jour le bouton
  btn.tick();
  
  stepper.run();
  
  if (debug) {
    static unsigned long lastTime = 0;
    if (currentTime - lastTime >= 1000) {
      lastTime = currentTime;
      printStatus();
    }    
  }
}

void PorteGarage::printStatus() {
      Serial.print("Current speed : ");
      Serial.print(stepper.speed());
      Serial.print("\tCurrent pos : ");
      Serial.print(stepper.currentPosition());
      Serial.print("\tTarget pos : ");
      Serial.print(stepper.targetPosition());
      Serial.print("\tDistance to go : ");
      Serial.print(stepper.distanceToGo());
      Serial.print("\tMax speed : ");
      Serial.print(stepper.maxSpeed());
      Serial.print("\tMax accel : ");
      Serial.println(stepper.acceleration());
}


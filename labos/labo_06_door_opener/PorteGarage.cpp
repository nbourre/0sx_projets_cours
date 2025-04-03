#include "PorteGarage.h"

PorteGarage* PorteGarage::instance = nullptr;

static void PorteGarage::buttonClick(PorteGarage *self) {
  // TODO : Complétez la fonction
  
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
    case FERMETURE:
      // TODO : Interrompre la fermeture
      break;
    // Réaliser les autres cas
    default:
      break;
  }
        
};

// Ouverture de la porte
void PorteGarage::ouvrir() {
  // TODO : Complétez la méthode
  // Implémentation de la méthode ouvrir()
  
  if (stepper.distanceToGo() == 0) {
    etat = OUVERT;
    
    sendEvent(false);
  }
}

// Préparation à l'ouverture
void PorteGarage::ouvrirEnter() {
  // TODO : Complétez la méthode
  // Faire les initialisations et instructions
  // nécessaires pour faire l'ouverture;
  
  etat = OUVERTURE;
  
  sendEvent(true);
}


// Fermeture de la porte
void PorteGarage::fermer() {
  // TODO : Complétez la méthode
  // Implémentation de la méthode fermer()
  // Effectuer les 3 tours pour fermer la porte
  // Lorsque ce sera fait, changer l'état de la porte

  if (stepper.distanceToGo() == 0) {
    etat = FERME;
    
    sendEvent(false);
  }
}

// Préparation à la fermeture
void PorteGarage::fermerEnter() {
  stepper.moveTo(-troisTours);
  etat = FERMETURE;
  
  sendEvent(true);
}

// Calibration de la porte
void PorteGarage::calibrer() {
  // TODO : Complétez la méthode
  // Implémentation de la méthode calibrer()
  
  // Appeler le callback lorsque la calibration sera
  // complétée
  // sendEvent(false);
}

// Attente d'un événement
// Il se peut qu'il n'y ait rien à faire dans cette méthode
void PorteGarage::attente() {
  // TODO : Complétez la méthode
}

void PorteGarage::sendEvent(bool moving) {
  if (callback) {
    callback(moving, "Garage");
  }
}

// Cette méthode doit être appelée à chaque itération de la boucle principale
void PorteGarage::update() {
  // TODO : Complétez la méthode
  // Implémentation de la méthode update()

  switch (etat) {
    case OUVERT:
    case FERME:
    case NOT_INIT:
      attente();
      break;
    case OUVERTURE:
      ouvrir();
      break;
    case FERMETURE:
      fermer();
      break;
    // Réaliser les autres cas manquants
    default:
      break;
  }

  
  
  // Met à jour le bouton
  btn.tick();
}

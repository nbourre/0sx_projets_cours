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
    case OUVERTURE:
      self->ouvrir();
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
}

// Préparation à l'ouverture
void PorteGarage::ouvrirEnter() {
  
  // Faire les initialisations et instructions
  // nécessaires pour faire l'ouverture;
  
  etat = OUVERTURE;      
}

// Sortie de l'ouverture, i.e. la porte est ouverte.
void  PorteGarage::ouvrirExit() {
  etat = OUVERT;  
}


// Fermeture de la porte
void PorteGarage::fermer() {
  // TODO : Complétez la méthode
  // Implémentation de la méthode fermer()
}

// Préparation à la fermeture
void PorteGarage::fermerEnter() {
  
}

// Sortie de l'état FERMETURE
void PorteGarage::fermerExit() {
  
}

void PorteGarage::calibrer() {
  // TODO : Complétez la méthode
  // Implémentation de la méthode calibrer()
}

PorteGarage::Etat PorteGarage::getEtat() {
  return etat;
}

void PorteGarage::update() {
  // TODO : Complétez la méthode
  // Implémentation de la méthode miseAJour()
  
  
  // Met à jour le bouton
  btn.tick();
}

// Exemple montrant comment détecter 
// le front montant et descendant 
// du signal du bouton
//


#define BTN_PIN 4

unsigned long currentTime = 0;
unsigned long lastTime = 0;

// Lorsque la lecture = 1, le bouton
// n'est pas appuyé
int btnPrecedent = 1;

// L'état utilisé pour la logique de l'application
int btnEtat = 1;
int btnEtatPrec = 1;

// Delai pour eviter les rebonds
int btnDelai = 25;

void setup() {
  Serial.begin(9600);
  
  pinMode(BTN_PIN, INPUT_PULLUP);

}

void loop() {
  currentTime = millis();
  
  int btnActuel = digitalRead(BTN_PIN);
  
  if (btnActuel != btnPrecedent) {
    lastTime = currentTime;        
  }
  
  // Ce petit delai permet d'éviter de lire un rebond
  if (currentTime - lastTime > btnDelai) {
    if (btnActuel != btnEtat) {
      btnEtat = btnActuel; // On enregistre l'état actuel
      Serial.print("Etat actuel:");
      Serial.println(btnEtat);
    }
  }
  
  btnPrecedent = btnActuel;
  
  // Cette partie est pour détecter les changements
  // d'état donc de 0 à 1 et de 1 à 0.
  if (btnEtat == 1 && btnEtatPrec == 0) {
    Serial.println("Bouton relache");
  } else if (btnEtat == 0 && btnEtatPrec == 1) {
    Serial.println("Bouton appuye");
  }
  
  btnEtatPrec = btnEtat;
}
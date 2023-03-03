// Exemple montrant comment détecter 
// le front montant et descendant 
// du signal du bouton
//


#define BTN_PIN 4

unsigned long currentTime = 0;

// Lorsque la lecture = 1, le bouton
// n'est pas appuyé
int btnPrecedent = 1;

void setup() {
  Serial.begin(9600);
  
  pinMode(BTN_PIN, INPUT_PULLUP);

}

void loop() {
  currentTime = millis();
  
  int btn = digitalRead(BTN_PIN);
  
  if (btn == 1 && btnPrecedent == 0) {
    Serial.println("Bouton relache!");
  } else if (btn == 0 && btnPrecedent == 1) {
    Serial.println("Bouton appuye!");
  }
  
  btnPrecedent = btn;
}
// Exemple de changement d'état de l'application
// Dans ce programme, je montre comment on peut
// changer les états de l'application en utilisant
// des fonctions
//
// Auteur : NB 20230126

int appState = 0;  // État de l'application
int ledState = LOW; // État du LED

void setup() {
  // Initialisation de la comm série
  Serial.begin(9600);

  // Initialisation du mode des pin
  pinMode (LED_BUILTIN, OUTPUT);

  // Seed comme dans minecraft
  randomSeed(analogRead(A0));

  Serial.println("Demarrage du programme");
}

// Fonction pour faire clignoter
void blink() {
  static int counter = 0;

  // Nombre aléatoire de clignotement
  static int nbBlinks = random(1, 10);

  digitalWrite(LED_BUILTIN, ledState);

  ledState = !ledState;

  delay(250);
  counter++;

  if (counter > nbBlinks) {
    // On reset les variables pour la prochaine fois
    nbBlinks = random(1, 10);
    counter = 0;

    // On change l'état de l'application
    appState = 1;

    // On écrit le prochain état
    Serial.println("fade");
  }
}

// Fonction pour faire varier
void fade() {
  static int counter = 0;

  // Nombre aléatoire de variation
  static int nbFades = random(1, 10); 

    // Calcul le délai requis pour 1 secondes
  static int brightness_delay = 1024 / 256;

  static int brightness = 0;

  int max_brightness = 255;

  analogWrite(LED_BUILTIN, brightness);

  brightness++;

  delay(brightness_delay);

  if (brightness >= max_brightness) {
    // remise à 0
    brightness = 0;
    counter++;
  }
  
  if (counter > nbFades) {
    // Reset des variables
    nbFades = random(1, 10);
    counter = 0;

    // On change l'état de l'application
    appState = 0;
    Serial.println("blink");
  }
}

void loop() { 
  switch(appState) {
    case 0:
      blink();
      break;
    case 1:
      fade();
      break;
  }
}

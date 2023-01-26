//Exemple de changement d'état de l'application
// Auteur : NB 20230126

unsigned long currentTime = 0;

int appState = 0;  // État de l'application
int ledState = LOW; // État du LED

void setup() {
  Serial.begin(9600);

  pinMode (LED_BUILTIN, OUTPUT);

  randomSeed(analogRead(A0));
  Serial.println("Demarrage du programme");
}

void etatDeClown() {
  static int counter = 0;
  static int nbBlinks = random(1, 10);

  int rate = random(50, 500);

    // Première exécution
  if (counter == 0) {
    Serial.print("nbBlinks : ");
    Serial.print(nbBlinks);
    Serial.print("\trate : ");
    Serial.println(rate);
  }

  digitalWrite(LED_BUILTIN, ledState);

  ledState = !ledState;

  delay(rate);
  counter++;

  if (counter > nbBlinks) {
    nbBlinks = random(1, 10);
    counter = 0;
    appState = 1;
    Serial.println("etatTDAH");
  }
}

void etatTDAH() {
  static int counter = 0;
  static int nbFades = random(1, 10);
  static int brightness = 0;
  static int max_brightness = random(20, 255);

  // Première exécution
  if (brightness == 0) {
    Serial.print("nbFades : ");
    Serial.print(nbFades);
    Serial.print("\tmax_brightess : ");
    Serial.println(max_brightness);
  }

  analogWrite(LED_BUILTIN, brightness);

  brightness++;

  delay(8);

  if (brightness > max_brightness) {
    max_brightness = random(20, 255);
    brightness = 0;
    counter++;
  }
  
  if (counter > nbFades) {
    nbFades = random(1, 10);
    counter = 0;
    appState = 0;
    Serial.println("etatDeClown");
  }
}

void loop() {
  currentTime = millis();
  
  switch(appState) {
    case 0:
      etatDeClown();
      break;
    case 1:
      etatTDAH();
      break;
  }


}

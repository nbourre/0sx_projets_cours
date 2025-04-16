#include "Affichage.h"

#define CLK_PIN 30
#define DIN_PIN 34
#define CS_PIN 32  // Chip Select

Affichage affichage(DIN_PIN, CLK_PIN, CS_PIN);

enum AppState { STOP,
                COUNTING,
                RESET };

AppState appState = STOP;

unsigned long currentTime = 0;

bool stopCmdFlag = false;
bool resetCmdFlag = false;
bool countCmdFlag = false;

int startValue = 0;
int endValue = 99;

String msg = "";

void appCountingState(unsigned long cT) {
  static unsigned long lastTime = 0;
  const int rate = 1000;
  static bool firstTime = true;

  static unsigned int counter = 0;

  if (firstTime) {
    firstTime = false;

    counter = startValue;
    return;
  }

  // Ligne nécessaire si l'on doit temporiser
  // les appels de cet état
  if (cT - lastTime < rate) return;

  lastTime = cT;

  counter++;
  if (counter > endValue) {
    counter = startValue;
  }
  affichage.setMessageFromInt(counter);

  bool transition = stopCmdFlag;

  if (transition) {
    firstTime = true;

    appState = STOP;
    stopCmdFlag = false;
  }

  bool transitionReset = resetCmdFlag;
  if (transition) {
    // Pas de changement d'état, on ne fait que redémarrer l'état
    firstTime = true;
    resetCmdFlag = false;
  }
}

void stopState(unsigned long ct) {
  static unsigned long lastTime = 0;
  const int rate = 500;
  static bool firstTime = true;

  static int posX = 0;
  static int dirX = 1;
  const int minX = 0;
  const int maxX = 7;
  const int maxY = 7;

  if (firstTime) {
    firstTime = false;
    posX = minX + 1;
    dirX = 1;
  }
  
  if (ct - lastTime < rate) return;
  lastTime = ct;

  if (posX <= 0 || posX >= maxX) {
    dirX = -dirX;
  }
  posX += dirX;

  // fix me!
  affichage.getU8G2()->clearBuffer();
  affichage.getU8G2()->drawLine(posX, 0, posX, maxY);
  affichage.getU8G2()->sendBuffer();


  bool transition = countCmdFlag;

  if (transition) {
    firstTime = true;
    appState = COUNTING;
  }
}

void stateManager(unsigned long ct) {
  // Adapter selon votre situation!
  switch (appState) {
    case STOP:
      stopState(ct);
      break;
    case COUNTING:
      appCountingState(ct);
      break;
  }
}

void analyserCommande(const String& tampon, String& commande, String& arg1, String& arg2) {
  commande = "";
  arg1 = "";
  arg2 = "";

  int firstSep = tampon.indexOf(';');
  int secondSep = tampon.indexOf(';', firstSep + 1);

  if (firstSep == -1) {
    // Pas de point-virgule, c'est peut-être "stop" ou autre commande sans paramètre
    commande = tampon;
    return;
  }

  // Extraire la commande
  commande = tampon.substring(0, firstSep);

  // Extraire arg1
  if (secondSep != -1) {
    arg1 = tampon.substring(firstSep + 1, secondSep);

    arg2 = tampon.substring(secondSep + 1);
  } else {
    // Il y a une seule valeur après la commande
    arg1 = tampon.substring(firstSep + 1);
  }
}


void serialEvent() {
  String tampon = Serial.readStringUntil('\n');


  Serial.println("Réception : " + tampon);

  String commande;
  String arg1, arg2;

  analyserCommande(tampon, commande, arg1, arg2);

  if (commande == "stop") {
    stopCmdFlag = true;
    Serial.println("cmd : stop");
  }

  if (commande == "rst") {
    resetCmdFlag = true;
    Serial.println("cmd : reset");
  }

  if (commande == "cnt") {
    startValue = arg1.toInt();
    endValue = arg2.toInt();
    countCmdFlag = true;
    Serial.println("cmd : count");
  }
}

#pragma region setup - loop
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  affichage.init();
  Serial.println("Setup done!");
}

void loop() {
  currentTime = millis();

  stateManager(currentTime);

  heartBeatTask(currentTime);
  //serialPrintTask(currentTime);

  //affichage.update();
}

void heartBeatTask(unsigned long ct) {
  static unsigned long lastTime = 0;
  const int rate = 4;

  static int ledValue = 0;
  static int dir = 1;

  if (ct - lastTime < rate) return;
  lastTime = ct;

  analogWrite (LED_BUILTIN, ledValue);
  
  ledValue += dir;

  if (ledValue <= 0 || ledValue >= 255) {
    dir = -dir;
  }

}

void serialPrintTask(unsigned long ct) {
  static unsigned long lastTime = 0;
  const int rate = 1000;

  if (ct - lastTime < rate) return;

  lastTime = ct;

  Serial.println(ct);

}

#pragma endregion

#pragma region Modèles

void xState(unsigned long cT) {
  static unsigned long lastTime = 0;
  const int rate = 500;

  static bool firstTime = true;

  if (firstTime) {
    // Code d'ENTRÉE c'est le
    //   code d'initialisation de l'état
    // Reset tes trucs
    // Exemples :
    //   Angle de référence, initialiser le lastTime,
    //   Chronomètre, etc.

    firstTime = false;
    return;
  }

  // Ligne nécessaire si l'on doit temporiser
  // les appels de cet état
  if (cT - lastTime < rate) return;

  lastTime = cT;

  // Code d'EXÉCUTION de l'état
  // Code de la job à faire

  // Code de TRANSITION
  // Il s'agit de la transition qui permet de sortir de l'état
  // Qu'est-ce qui fait que l'on sort de l'état?
  bool transition = false;

  // Il est possible d'avoir plusieurs transitions

  if (transition) {
    // Code de SORTIE
    // Code pour terminer l'état

    firstTime = true;

    // appState = PROCHAIN_ETAT;
  }
}

// Modèle de tâche qui ne retourne aucune valeur.
void xTask(unsigned long ct) {
  static unsigned long lastTime = 0;
  unsigned long rate = 500;

  if (ct - lastTime < rate) {
    return;
  }

  lastTime = ct;

  // Faire le code de la tâche ici
}

// Modèle de tâche avec retour de valeur.
// Exemple d'utilisation :
//   - Mesure de distance, température, etc.
int xTaskWithReturn(unsigned long ct) {
  static unsigned long lastTime = 0;
  unsigned long rate = 500;
  static int lastResult = 0;
  int result = 0;

  if (ct - lastTime < rate) {
    return result;
  }

  lastTime = ct;

  // Faire le code de la tâche ici
  result = 1;

  lastResult = result;

  return result;
}

#pragma endregion
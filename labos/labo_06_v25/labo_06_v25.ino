#include "Affichage.h"

#define CLK_PIN 30
#define DIN_PIN 34
#define CS_PIN  32  // Chip Select

Affichage affichage(DIN_PIN, CLK_PIN, CS_PIN);

enum AppState {STOP, COUNTING, RESET};

AppState appState = STOP;

unsigned long currentTime = 0;

bool stopFlag = false;
bool resetFlag = false;

void appCountingState(unsigned long cT) {
  static unsigned long lastTime = 0;
  const int rate = 100;
  static bool firstTime = true;
  
  static unsigned int counter = 0;

  if (firstTime) {
    firstTime = false;

    counter = 0;
    return;
  }

  // Ligne nécessaire si l'on doit temporiser
  // les appels de cet état
  if (cT - lastTime < rate) return;

  lastTime = cT;
  
  bool transition = stopFlag;

  if (transition) {
    firstTime = true;
    
    appState = STOP;    
    stopFlag = false;
  }
  
  bool transitionReset = resetFlag;
  if (transition) {
    
    appState = STOP; 
    resetFlag = false;
  }
  
}

void stateManager(unsigned long ct) {
  // Adapter selon votre situation!
  switch (appState) {
    case STOP:
      
      break;
    case COUNTING:
      appCountingState(ct);
      break;
  }
}

#pragma region setup-loop
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  currentTime = millis();
  
  stateManager(currentTime);

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
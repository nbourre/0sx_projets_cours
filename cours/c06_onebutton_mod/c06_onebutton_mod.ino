#include "OneButton.h"

// Les tâches pouvant être faites
typedef enum {
  TASK_OFF,  // set LED "OFF".
  TASK_ON,   // set LED "ON"
  TASK_SLOW, // blink LED "SLOW"
  TASK_FAST  // blink LED "FAST"
} 
Tasks;

#define PIN_INPUT 2
#define PIN_LED 13

unsigned long currentTime = 0;

// Configurer un bouton avec LOW comme valeur d'entrée et
// activer la résistance de pull-up. Voir la documentation ou
// le code source. (CTRL+click sur le nom de la classe)
OneButton button(PIN_INPUT, true, true);

 // Aucune tâches au démarrage
Tasks nextTask = TASK_OFF;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);

  // Attacher la fonction qui s'exécutera
  // lorsqu'un clic sera détecter
  button.attachClick(myClickFunction);

  // Attacher la fonction qui s'exécutera
  // lorsqu'un double-clic sera détecter
  button.attachDoubleClick(myDoubleClickFunction);

  // Configurer un délai de debounce. Par défaut 50 ms
  button.setDebounceTicks(25);
  
  Serial.println ("Configuration complétée");
}

void loop() {
  currentTime = millis();

  // Cette fonction est OBLIGATOIRE pour
  // surveiller le bouton. C'est comme un tâche de
  // surveillance
  button.tick();
  
  switch (nextTask) {
    case TASK_OFF:
      turnOffTask();
      break;
    case TASK_ON:
      turnOnTask();
      break;
    case TASK_SLOW:
      blinkTask(currentTime);
      break;
    case TASK_FAST:
      fadeTask(currentTime);
      break;    
  }
  
  serialPrintTask(currentTime);
}

void turnOffTask() {
  digitalWrite(PIN_LED, LOW);  
}

void turnOnTask() {
  digitalWrite(PIN_LED, HIGH);
}

void blinkTask(unsigned long now) {
  static unsigned int lastTime = 0;
  const int rate = 500;
  
  if (now - lastTime >= rate) {
    lastTime = now;
    digitalWrite (PIN_LED, !digitalRead(PIN_LED));
    Serial.print(".");
  }
}

void fadeTask(unsigned long now) {
  static unsigned int lastTime = 0;
  static byte brightness = 1;
  static byte direction = 1;  
  
  const int rate = 8;
  
  if (now - lastTime >= rate) {
    lastTime = now;
    
    if (brightness <= 0 || brightness >= 255) {
      direction = -direction;
    }
    
    analogWrite (PIN_LED, brightness);
    
    brightness += direction;
  }
}

// Cette fonction sera appelée lorsqu'il n'y aura qu'un seul clic du bouton
void myClickFunction() {
  if (nextTask == TASK_OFF)
    nextTask = TASK_ON;
  else
    nextTask = TASK_OFF;
  
  Serial.println(nextTask);
}


// Cette fonction sera appelée lorsqu'il y aura un double-clic
void myDoubleClickFunction() {
  if (nextTask == TASK_ON) {
    nextTask = TASK_SLOW;

  } else if (nextTask == TASK_SLOW) {
    nextTask = TASK_FAST;

  } else if (nextTask == TASK_FAST) {
    nextTask = TASK_ON;
  }
  Serial.println(nextTask);
}

void serialPrintTask(unsigned long now) {
  static unsigned int lastTime = 0;
  const int rate = 1000;
  
  if (now - lastTime >= rate) {
    lastTime = now;
    
    Serial.print(now);
    Serial.print(" - Tache : ");
    Serial.println(nextTask);
  }   
}

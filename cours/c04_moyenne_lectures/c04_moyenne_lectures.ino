unsigned long currentTime = 0;

// String est une classe qui permet de manipuler des chaînes de caractères
String msg = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
    currentTime = millis();
    int val = sensorTask();
    msg += "Lumiere:" + String(val);
    serialPrintTask();
}

// Tâche de lecture de la valeur de la photorésistance
int sensorTask() {
    static unsigned long lastTime = 0;
    static unsigned int valSum = 0;
    static int val = 0;
    static int sampleCount = 0;

    // Taux de rafraîchissement de la lecture de la valeur de la photorésistance
    int rate = 100;
    int nbSamples = 16;

    if (currentTime - lastTime > rate) {
        lastTime = currentTime;

        // Somme des valeurs lues
        valSum += analogRead(A0);

        if (++sampleCount >= nbSamples) {
             // Décalage de 4 bits vers la droite équivaut à la division par 16
             // C'est plus rapide que la division
            val = valSum >> 4;

            // Remise à zéro des variables
            valSum = 0;
            sampleCount = 0;
        }
    }

    return val;
}

// Tâche d'envoi des données dans le traceur série
void serialPrintTask() {
    static unsigned long serialPrintPrevious = 0;
    int serialPrintInterval = 100;

    // Si ce n'est pas le moment, on sort de la fonction immédiatement
    if (currentTime - serialPrintPrevious < serialPrintInterval) return;

    serialPrintPrevious = currentTime;

    if (msg != "") {
        Serial.println(msg);
        msg = "";
    }
}

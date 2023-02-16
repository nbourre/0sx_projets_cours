unsigned long currentTime = 0;
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

int sensorTask() {
    static unsigned long lastTime = 0;
    static unsigned int valSum = 0;
    static int val = 0;
    static int sampleCount = 0;

    int rate = 100;
    int nbSamples = 10;

    if (currentTime - lastTime > rate) {
        lastTime = millis();
        valSum += analogRead(A0);

        if (++sampleCount >= nbSamples) {
            val = valSum / nbSamples;
            valSum = 0;
            sampleCount = 0;
        }
    }

    return val;
}

void serialPrintTask() {
    static unsigned long serialPrintPrevious = 0;
    int serialPrintInterval = 100;

    if (currentTime - serialPrintPrevious < serialPrintInterval) return;

    serialPrintPrevious = currentTime;

    if (msg != "") {
        Serial.println(msg);
        msg = "";
    }
}
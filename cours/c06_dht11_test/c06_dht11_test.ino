#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11

unsigned long currentTime;

// Construction de l'objet
// dht
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  currentTime = millis();
  
  dhtTask(currentTime);
}

// Tâche de lecture du DHT11
void dhtTask(unsigned long now) {
  static unsigned long lastTime = 0;
  const int rate = 2000;
  
  if (now - lastTime >= rate) {
    // La lecture de la température peut prendre jusqu'à
    // 2 secondes. C'est un capteur lent.
    
    // De plus, ce n'est pas vraiment utile de prendre
    // la température de l'air ampbiant fréquemment
        
    lastTime = now;
    
    
    // Lecture de l'humidité    
    float h = dht.readHumidity();
    
    // Lecture de la température en °C
    float t = dht.readTemperature();
    
    // Lecture de la température en °F (paramètre true)
    float f = dht.readTemperature(true);

    // Valider que toutes les lectures sont bonnes
    // Sinon on retourne plus tot.
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Echec de lecture du DHT!"));
      return;
    }

    // Calcule de l'indice humidex en °C
    // 3e paramètre : isFahreheit = false
    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print(F("Humidite: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(f);
    Serial.print(F("°F  Heat index: "));
    Serial.print(hic);
    Serial.println(F("°C "));
  }
}

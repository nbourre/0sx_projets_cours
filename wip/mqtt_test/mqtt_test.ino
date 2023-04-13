/*
*  IMPORTANT! S'assurer que le Wifi est configuré avant de téléverser ce code.
*  Projet : Examples --> WifiEspAT --> Tools --> SetupWifiPersistentConnection
*/

#include <WiFiEspAT.h>
#include <PubSubClient.h>
#include <DHT.h>

// Emuler Serial1 sur les broches 6/7 si non présent
#if defined(ARDUINO_ARCH_AVR) && !defined(HAVE_HWSERIAL1)
#include <SoftwareSerial.h>
SoftwareSerial Serial1(6, 7);  // RX, TX
#define AT_BAUD_RATE 9600
#else
#define AT_BAUD_RATE 115200
#endif

#define DEVICE_NAME "NickProf"
#define MQTT_PORT 1883
#define MQTT_USER "etdshawi"
#define MQTT_PASS "shawi123"

// Serveur MQTT du prof
const char* server = "216.128.180.194";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

unsigned long currentTime = 0;

#define DHT_PIN 10
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);


void wifiInit() {
  // Initialisation du module WiFi.
  Serial1.begin(AT_BAUD_RATE);
  WiFi.init(Serial1);

  
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println();
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true) {
      // Clignote rapidement pour annoncer l'erreur
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(50);
    }
  }
  
  // waiting for connection to Wifi network set with the SetupWiFiConnection sketch
  Serial.println("Waiting for connection to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  } 
  
  printWifiStatus();
}

void printWifiStatus() {

  // imprimez le SSID du réseau auquel vous êtes connecté:
  char ssid[33];
  WiFi.SSID(ssid);
  Serial.print("SSID: ");
  Serial.println(ssid);

  // imprimez le BSSID du réseau auquel vous êtes connecté:
  uint8_t bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  uint8_t mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  printMacAddress(mac);

  // imprimez l'adresse IP de votre carte:
  IPAddress ip = WiFi.localIP();
  Serial.print("Adresse IP: ");
  Serial.println(ip);

  // imprimez la force du signal reçu:
  long rssi = WiFi.RSSI();
  Serial.print("force du signal (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}

// Gestion des messages reçues de la part du serveur MQTT
void mqttEvent(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message recu [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void periodicTask() {
  static unsigned long lastTime = 0;
  static char message[100] = "";
  static char szTemp[6];
  static char szHum[6];
  const unsigned int rate = 10000;

  static float temp = 0;
  static float hum = 0;

  if (currentTime - lastTime < rate) return;

  lastTime = currentTime;

  temp = dht.readTemperature();
  hum = dht.readHumidity();

  dtostrf(temp, 4, 1, szTemp);
  dtostrf(hum, 4, 1, szHum);

  sprintf(message, "{'temp' : %s, 'hum':%s }", szTemp, szHum);

  Serial.print("Envoie : ");
  Serial.println(message);

  if (!client.publish("test", message)) {
    Serial.println("Incapable d'envoyer le message!");
  } else {
    Serial.println("Message envoyé");
  }
}


void setup() {
  Serial.begin(9600);
  pinMode (LED_BUILTIN, OUTPUT);
  
  wifiInit();
  
  client.setServer(server, MQTT_PORT);
  client.setCallback(mqttEvent);
  
  if(!client.connect(DEVICE_NAME, MQTT_USER, MQTT_PASS)) {
    Serial.println("Incapable de se connecter sur le serveur MQTT");
  }

  dht.begin();
  
  // Configuration terminée
  Serial.println("Setup done");
  delay(1000);
}

void loop() {
  currentTime = millis();
  // Mettre le code à exécuter continuellement

  periodicTask();
}


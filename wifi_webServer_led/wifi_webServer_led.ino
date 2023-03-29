/*
Serveur Web WiFi

Un simple serveur web qui affiche la valeur des broches d'entrée analogique.

Créé le 13 Juillet 2010
par dlf (Metodo2 srl)
modifié le 31 mai 2012
par Tom Igoe
modifié en juillet 2019 pour la bibliothèque WiFiEspAT
par Juraj Andrassy https://github.com/jandrassy
*/

#include <WiFiEspAT.h>
#include "RingBuffer.h"

// Emuler Serial1 sur les broches 6/7 si non présent
#if defined(ARDUINO_ARCH_AVR) && !defined(HAVE_HWSERIAL1)
#include <SoftwareSerial.h>
SoftwareSerial Serial1(6, 7);  // RX, TX
#define AT_BAUD_RATE 9600
#else
#define AT_BAUD_RATE 115200
#endif

WiFiServer server(80);

// Utilise un tampon circulaire pour améliorer
// la vitesse et réduire l'allocation de mémoire
RingBuffer buf(8);

int ledStatus = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial)
    ;

  Serial1.begin(AT_BAUD_RATE);
  WiFi.init(Serial1);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("La communication avec le module WiFi a échoué !");
    // ne pas continuer
    while (true)
      ;
  }

  // En attendant la connexion au réseau Wifi configuré avec le sketch SetupWiFiConnection
  Serial.println("En attente de connexion au WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  }
  Serial.println();

  server.begin();

  IPAddress ip = WiFi.localIP();
  Serial.println();
  Serial.println("Connecté au réseau WiFi.");
  Serial.print("Pour accéder au serveur, entrez \"http://");
  Serial.print(ip);
  Serial.println("/\" dans un navigateur web.");
}

void loop() {
  wifiTask();
}

void wifiTask() {
    WiFiClient client = server.available();

  // Si vous obtenez un client
  if (client) {
    IPAddress ip = client.remoteIP();
    Serial.print("nouveau client ");
    Serial.println(ip);

    // Initialiser le tampon circulaire
    buf.init();

    // Boucler tant que le client est connecté
    while (client.connected()) {

      // Si des octets sont disponibles à partir du client
      if (client.available()) {

        char c = client.read();  // lire un octet et
        buf.push(c);             // le pousser dans le tampon circulaire

        // Écrire dans le flux série va ralentir le code
        // the receiving of data from the ESP filling the serial buffer
        //Serial.write(c);

        // Vérifiez si la requête HTTP est terminée en détectant deux caractères
        // de nouvelle ligne consécutifs "\r\n\r\n", puis envoyez une réponse
        if (buf.endsWith("\r\n\r\n")) {
          sendHttpResponse(client);
          break;
        }

        // Regarder si le client a demandé était "GET /H" or "GET /L":
        if (buf.endsWith("GET /H")) {
          Serial.println("Turn led ON");
          digitalWrite(LED_BUILTIN, HIGH);
          ledStatus = 1;
        } else if (buf.endsWith("GET /L")) {
          Serial.println("Turn led OFF");
          digitalWrite(LED_BUILTIN, LOW);

          ledStatus = 0;
        }
      }
    }

    // fermer la connexion:
    client.stop();
    Serial.println("client déconnecté");
  }

}

void sendHttpResponse(WiFiClient client) {
  sendHTTPHeader(client);

  // Le contenu de la réponse HTTP suit l'en-tête :
  // il affiche l'état de la LED et fournit des liens pour allumer ou éteindre la LED.
  client.print("The LED is ");
  client.print(ledStatus);
  client.println("<br>");
  client.println("<br>");

  client.println("Click <a href=\"/H\">here</a> turn the LED on<br>");
  client.println("Click <a href=\"/L\">here</a> turn the LED off<br>");

  // The HTTP response ends with another blank line:
  client.println();
}

void sendHTTPHeader(WiFiClient client) {
  // Les en-têtes HTTP commencent toujours par un code de réponse (par exemple, HTTP/1.1 200 OK)
  // et un type de contenu pour que le client sache ce qui arrive, puis une ligne vide.
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
}

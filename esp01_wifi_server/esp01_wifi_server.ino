/*
 Exemple WiFiEsp : WebServer

 Un serveur web simple qui montre la valeur des entrées analogiques
 via une page web en utilisant un module ESP8266.
 Ce programme affichera l'adresse IP de votre module ESP8266 (une fois connecté)
 dans le moniteur série. À partir de là, vous pouvez ouvrir cette adresse dans un navigateur web
 pour afficher la page web.
 La page web sera automatiquement rafraîchie toutes les 20 secondes.

 Pour plus de détails, voir : http://yaab-arduino.blogspot.com/p/wifiesp.html
*/

#include "WiFiEsp.h"

char ssid[] = "Twim";            // le nom de votre réseau (SSID)
char pass[] = "12345678";        // le mot de passe de votre réseau
int status = WL_IDLE_STATUS;     // l'état de la radio WiFi
int reqCount = 0;                // nombre de requêtes reçues

WiFiEspServer server(80);


void setup()
{
  // initialiser le port série pour le débogage
  Serial.begin(115200);
  // initialiser le port série pour le module ESP
  Serial3.begin(115200);
  // initialiser le module ESP
  WiFi.init(&Serial3);

  // vérifier la présence du module
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Module WiFi non détecté");
    // ne pas continuer
    while (true);
  }

  // essayer de se connecter au réseau WiFi
  while ( status != WL_CONNECTED) {
    Serial.print("Tentative de connexion au SSID WPA : ");
    Serial.println(ssid);
    // Se connecter au réseau WPA/WPA2
    status = WiFi.begin(ssid, pass);
  }

  Serial.println("Vous êtes connecté au réseau");
  printWifiStatus();
  
  // démarrer le serveur web sur le port 80
  server.begin();
}


void loop()
{
  // écouter les clients entrants
  WiFiEspClient client = server.available();
  if (client) {
    Serial.println("Nouveau client");
    // une requête HTTP se termine par une ligne vide
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // si vous avez atteint la fin de la ligne (reçu un caractère de nouvelle ligne) et que la ligne est vide, la requête HTTP est terminée,
        // donc vous pouvez envoyer une réponse
        if (c == '\n' && currentLineIsBlank) {
          Serial.println("Envoi de la réponse");
          
          // envoyer un en-tête de réponse HTTP standard
          // utiliser \r\n au lieu de plusieurs println pour accélérer l'envoi des données
          client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "Connection: close\r\n"  // la connexion sera fermée après l'achèvement de la réponse
            "Refresh: 20\r\n"        // rafraîchir la page automatiquement toutes les 20 sec
            "\r\n");
          client.print("<!DOCTYPE HTML>\r\n");
          client.print("<html>\r\n");
          client.print("<h1>Bonjour le monde !</h1>\r\n");
          client.print("Requêtes reçues : ");
          client.print(++reqCount);
          client.print("<br>\r\n");
          client.print("Entrée analogique A0 : ");
          client.print(analogRead(0));
          client.print("<br>\r\n");
          client.print("</html>\r\n");
          break;
        }
        if (c == '\n') {
          // vous commencez une nouvelle ligne
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // vous avez reçu un caractère sur la ligne actuelle
          currentLineIsBlank = false;
        }
      }
    }
    // donner au navigateur web le temps de recevoir les données
    delay(10);

    // fermer la connexion :
    client.stop();
    Serial.println("Client déconnecté");
  }
}


void printWifiStatus()
{
  // afficher le SSID du réseau auquel vous êtes connecté
  Serial.print("SSID : ");
  Serial.println(WiFi.SSID());

  // afficher l'adresse IP de votre module WiFi
  IPAddress ip = WiFi.localIP();
  Serial.print("Adresse IP : ");
  Serial.println(ip);
  
  // indiquer où aller dans le navigateur
  Serial.println();
  Serial.print("Pour voir cette page en action, ouvrez un navigateur à l'adresse http://");
  Serial.println(ip);
  Serial.println();
}

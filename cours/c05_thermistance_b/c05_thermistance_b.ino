// Constantes
const int thermistorPin = A0; // broche analogique A0
const int numReadings = 10; // nombre de lectures
const float B = 3975; // coefficient B de la thermistance
const float R0 = 100000; // résistance de la thermistance à 25°C

// Variables
float tempC; // température en degrés Celsius
float tempF; // température en degrés Fahrenheit
float resistance; // résistance de la thermistance
float average; // valeur moyenne de la résistance
float readings[numReadings]; // tableau de valeurs de résistance
int index = 0; // index du tableau
int total = 0; // valeur totale des valeurs de résistance

void setup() {
  Serial.begin(9600); // initialise le moniteur série
}

void loop() {
  // lit la valeur de la thermistance
  int reading = analogRead(thermistorPin);
  
  // ajoute la valeur de la thermistance au tableau
  total = total - readings[index];
  readings[index] = reading;
  total = total + readings[index];
  index = index + 1;
  
  // si l'index dépasse la taille du tableau, on le remet à 0
  if (index >= numReadings) {
    index = 0;
  }
  
  // calcule la valeur moyenne de la résistance
  average = total / numReadings;
  
  // calcule la résistance de la thermistance
  resistance = (1023 / average) - 1;
  resistance = R0 / resistance;
  
  // calcule la température en degrés Celsius
  tempC = 1 / (log(resistance / R0) / B + 1 / 298.15) - 273.15;
  
  // calcule la température en degrés Fahrenheit
  tempF = (tempC * 9.0) / 5.0 + 32.0;
  
  // affiche la température sur le moniteur série
  Serial.print("Temperature : ");
  Serial.print(tempC);
  Serial.print(" C / ");
  Serial.print(tempF);
  Serial.println(" F");
  
  delay(1000); // attend 1 seconde
}
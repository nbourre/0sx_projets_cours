// Sensor pins
#define sensorPower 2 // Pin pour allumer le capteur
#define sensorPin A0 // Pin du signal

// Value for storing water level
int sensorValue = 0;

unsigned long currentTime = 0;

void setup() {
	// Set D7 as an OUTPUT
	pinMode(sensorPower, OUTPUT);
	
	// Set to LOW so no power flows through the sensor
	digitalWrite(sensorPower, LOW);
	
	Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  
  sensorTask();
	serialTask();
}

void serialTask() {
  static unsigned long lastTime = 0;
  int rate = 1000;
  
  if (currentTime - lastTime >= rate) {
    lastTime = currentTime;
    
    Serial.print("Value:");
    Serial.println(sensorValue);
    
  }
}


int sensorTask() {
  static unsigned long lastTime = 0;
  static int readFlag = 0;
  
  static unsigned long lastRead = 0;
  static int lastValue = 0;
  
  int rate = 500;
  int wait = 10;
  
  if (readFlag) {
    if (currentTime - lastRead >= wait) {
      sensorValue = analogRead(sensorPin);		// Read the analog value form sensor      
      digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
      lastValue = sensorValue;
      
      readFlag = 0;
    }    
    
  } else if (currentTime - lastTime >= rate) {
    lastTime = currentTime;
    lastRead = currentTime;
    
    digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
        
    readFlag = 1;    
  }
  
  return lastValue;	
}
int mode = 0;
int count = 0;

int brightness = 0;  // how bright the LED is
int fadeAmount = -4;  // how many points to fade the LED by

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (mode == 0) {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(250);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(250);                      // wait for a second
    count++;
    
    if (count >= 1) {
      mode = 1;
      brightness = 255;
    }
  } else {
      // set the brightness of pin 9:
      analogWrite(LED_BUILTIN, brightness);

      // change the brightness for next time through the loop:
      brightness = brightness + fadeAmount;

      // wait for 30 milliseconds to see the dimming effect
      delay(16);
      
      if (brightness <= 0) {
        mode = 0;
        count = 0;
      }
  }
}

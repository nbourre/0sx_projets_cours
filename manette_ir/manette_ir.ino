#include <IRremote.hpp>

const int RECV_PIN = 26;

void setup(){
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  setFeedbackLED(true);
  
}

void loop(){
  if (IrReceiver.decode()){
    Serial.println("--------");
    Serial.print("Protocole : ");
    Serial.println(IrReceiver.getProtocolString());
    Serial.print("Commande : ");
    Serial.println(IrReceiver.decodedIRData.command);
    Serial.print("Brute : ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    Serial.print("Flags : ");
    Serial.print(IrReceiver.decodedIRData.flags);
    
    if (IrReceiver.decodedIRData.flags) {
      Serial.println(" (Repetition)");      
    } else {
      Serial.println("");
    }
    
    IrReceiver.resume();
  }
}
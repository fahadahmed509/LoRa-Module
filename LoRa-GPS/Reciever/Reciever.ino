//Receiver

#include <LoRa.h> 
const int ledPin = 3;   // indicator LED

String latitude_String = "";
String longitude_String = "";
int SyncWord = 0x22;


String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);  
  digitalWrite(ledPin , LOW);
   
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
    while (1);
  }
   LoRa.setSpreadingFactor(12);           // ranges from 6-12,default 7 see API docs
   LoRa.setSignalBandwidth(62.5E3);           // for -139dB (page - 112)
   LoRa.setCodingRate4(8);                   // for -139dB (page - 112)
   LoRa.setSyncWord(SyncWord);           // ranges from 0-0xFF, default 0x12, see API docs

}
bool i=0;
int priviousValue = 0;
int liveValue = 0;

void loop() { 
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) { 
    String inputString = "";
    while (LoRa.available())
    {
      /*int inChar = LoRa.read();
      inString += (char)inChar;
      lattitude_String = inString.toInt();*/
      
      char inChar = (char)LoRa.read();
      inputString += inChar;  
        
    }
      Serial.println(inputString);  
      delay(50);     
      LoRa.packetRssi(); 
  }
} 

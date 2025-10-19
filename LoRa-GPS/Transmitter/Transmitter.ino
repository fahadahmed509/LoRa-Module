//TRANSMITTER
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <LoRa.h>

int Tx = 4;
int Rx = 3;
SoftwareSerial gpsSerial(Tx,Rx);
TinyGPSPlus gps;

int counter = 0;
float lattitude,longitude;
String lattitude_String = "";
String longitude_String = "";

int SyncWord = 0x22;

void setup() {

 gpsSerial.begin(9600);
 Serial.begin(9600);
  while (!Serial);  
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }

    LoRa.setSpreadingFactor(12);           // ranges from 6-12,default 7 see API docs
    LoRa.setSignalBandwidth(62.5E3 );           // for -139dB (page - 112)
    LoRa.setCodingRate4(8);                   // for -139dB (page - 112)
    LoRa.setSyncWord(SyncWord);

  }

void loop()
{
  while (gpsSerial.available())
  {
    int data = gpsSerial.read();
    if (gps.encode(data))
    {
      lattitude = (gps.location.lat());
      longitude = (gps.location.lng());
      lattitude_String = String(lattitude,5);
      longitude_String = String(longitude,5);

      Serial.print ("lattitude: ");
      Serial.print (lattitude_String);
      Serial.print ("   longitude: ");
      Serial.println (longitude_String);

      LoRa.beginPacket();  
      LoRa.print(lattitude_String);
      LoRa.print(",");
      LoRa.print(longitude_String);
      LoRa.endPacket();
      delay(8000);
  

    }
  }
}
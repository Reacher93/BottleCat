#include <SoftwareSerial.h>

int rx = 7; // pin 7 als tx definiert
int tx = 8; // pin 8 als rx definiert

SoftwareSerial BT(rx, tx); //Serialschnitstelle BT definiert

String var; //String var definiert

void setup()
{
BT.begin(9600); //starte Serialschnitstelle mit der Baudrate 9600
Serial.begin(4800);
Serial.println("Monitor läuft");
}

void loop()
{
if (BT.available()) //BT abfrage
{
    var = BT.readString();  //BT Wert wird in Variable eingelesen
    
    if (var == "1"){
      Serial.println("Verbindung ok");
      Serial.println(var);
    }
    else if (var == "2"){ 
      Serial.println("Flasche wird geöffnet");
      Serial.println(var);
    }
    Serial.println(var);
  }

delay(500);

//Für Test Monitoreingabe auf App anzeigen
String Mvar;
if (Serial.available())  //Wert aus Monitor abfragen
  {
  Mvar = Serial.readString();
  }
  BT.print(Mvar);
}

/*
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){

  if(type == WStype_TEXT){

    rx_from_brower = "";

   for(int i = 0; i < length; i++){

   // rx_from_brower = (rx_from_brower.concat((char) payload[i]));

   rx_from_brower += (char)payload[i];

    }

    Serial.println(rx_from_brower);
    */

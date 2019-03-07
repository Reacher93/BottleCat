#include <BluetoothSerial.h>    //Benötigte Library für die Serielle Bluetooth Übertragung mit dem ESP32 Modul

/*int tx = 7; // pin 7 als tx definiert
int rx = 8; // pin 8 als rx definiert -> Für das ESP32 Modul nicht benötigt*/

BluetoothSerial BT;   // für EPS32 nicht benötigt(tx, rx); //Serialschnitstelle BT definiert

String var; //String var definiert

void setup()
{
BT.begin("Bottle-Cat"); //starte Serialschnitstelle mit Bluetooth device name
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

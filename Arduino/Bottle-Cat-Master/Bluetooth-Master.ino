//#include <BluetoothSerial.h>    //Benötigte Library für die Serielle Bluetooth Übertragung mit dem ESP32 Modul

/*int tx = 7; // pin 7 als tx definiert
int rx = 8; // pin 8 als rx definiert -> Für das ESP32 Modul nicht benötigt*/

//BluetoothSerial BT;   //Serialschnitstelle BT definiert

void initBT(){    //Initialisierung vom Bluetooth
  BT.begin("Bottle-Cat");   //starte Serialschnitstelle mit Bluetooth device name
}

String BTabfragen(){
  String Vread;   //String Vread definiert
  if (BT.available()) //BT abfrage
  {
    Vread = BT.readString();  //BT Wert wird in Variable eingelesen
  }
  return(Vread);
}

void BTsenden(String Vsend){
  if (Serial.available())  //Wert aus Monitor abfragen
  {
    Vsend = Serial.readString();
  }
  BT.print(Vsend);
}

/*
void setup()
{
  initBT();
  
  Serial.begin(4800);
  Serial.println("Monitor läuft");
}

void loop()
{
    if (BTabfragen() == "1"){
      Serial.println("Verbindung ok");
      Serial.println(BTabfragen());
    }
    else if (BTabfragen() == "2"){ 
      Serial.println("Flasche wird geöffnet");
      Serial.println(BTabfragen());
    }
    Serial.println(BTabfragen());

delay(500);

}
*/

//Gehört zum Master Sketch; Bottle-Cat

#include <BluetoothSerial.h>    //Benötigte Library für die Serielle Bluetooth Übertragung mit dem ESP32 Modul

BluetoothSerial BT;   //Serielle Bluetooth Schnittstelle BT definiert

void initBT(){    //Initialisierung vom Bluetooth
  BT.begin("Bottle-Cat");   //starte Serialschnitstelle mit Bluetooth device name
}

String BTabfragen(){    //Funktion für empfangen von Strings über BT
  String Vread;
  if (BT.available())   //BT abfrage
  {
    Vread = BT.readString();  //BT Wert wird in Variable eingelesen
  }
  return(Vread);
}

void BTsenden(String Vsend){    //Funktion für senden über BT (noch nicht verwendet)
  BT.print(Vsend);
}

#include <SoftwareSerial.h>

int tx = 7; // pin 7 als tx definiert
int rx = 8; // pin 8 als rx definiert
SoftwareSerial BT(tx, rx); //Serialschnitstelle BT definiert

void setup()
{
BT.begin(9600); //starte Serialschnitstelle mit der Baudrate 9600
}

char test; //test Variable definiert

void loop()
{
if (BT.available()) //BT abfrage
{
    test=BT.read(); //BT Wert wird in Variable eingelesen
}
delay(50);
Serial.print(test);
}

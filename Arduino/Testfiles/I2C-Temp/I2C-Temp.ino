#include <Wire.h>

int TempAdd = 0x40;        //Temperatursensor I2C Hex Address

#define TempO 0x03       //Interne Adresse für Objekt Temperatur

void setup(){
    Wire.begin();       //Starte Wire library
    delay(100);
    Serial.begin(9600);     //Zum Test Anzeigen der Messresultete auf dem Serial Monitor
}

void loop(){

    float OT;       //Variable für Objekt Temperatur

    Wire.beginTransmission(TempAdd);        //Starte Kommunikation zum Temperatursensor
    Wire.write(TempO);     //Abfrage der Objekt Temperatur

    Wire.endTransmission();     //Beendet die Kommunikation

    Wire.requestFrom(TempAdd,1);        //Abfrage der übertragenen Daten von den zwei Limit Temperaturen (?2 Daten oder 20 bits?)

    if(Wire.available()<=1){        //Nachfragen ob die zwei passenden Daten verfügbar sind und in die ensprechenden Varianlen einlesen (OT)
        OT = Wire.read();
    }

    Serial.print("Die gemessene Temperatur ist: ");
    Serial.println(OT);
    delay(500);

}

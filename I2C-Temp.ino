#include <Wire.h>

int TempAdd = 0x40;        //Temperatursensor I2C Hex Address

#define TempHL = 0x06       //Interne Adresse für Objekt Temperatur High Limit
#define TempLL = 0x07       //Interne Adresse für Objekt Temperatur Low Limit

void setup(){
    Wire.begin();       //Starte Wire library
    delay(100);
    Serial.begin(9600);     //Zum Test Anzeigen der Messresultete auf dem Serial Monitor
}

void loop(){

    float HT;       //Variable für High Temperatur definiert
    float LT;       //Variable für Low Temperatur definiert
    float MT;       //Variable für mittlere Temperatur

    Wire.beginTransmission(TempAdd);        //Starte Kommunikation zum Temperatursensor
    Wire.write(TempHL);     //Abfrage der High Limit Temperatur
    Wire.write(TempLL);     //Abfrage der Low Limit Temperatur

    Wire.endTransmission();     //Beendet die Kommunikation

    Wire.requestFrom(TempAdd,2);        //Abfrage der übertragenen Daten von den zwei Limit Temperaturen (?2 Daten oder 20 bits?)

    if(Wire.available()<=2){        //Nachfragen ob die zwei passenden Daten verfügbar sind und in die ensprechenden Varianlen einlesen (HT, LT)
        HT = Wire.read();
        LT = Wire.read();
    }

    MT = (HT+LT)/2;     //Mittelwert der Temperaturen berechnen

    Serial.print("Die gemessene Temperatur ist: ");
    Serial.println(MT);

}
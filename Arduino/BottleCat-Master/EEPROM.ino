/*
Programm um remanete Variablen in der EEPROM zu speicher und wieder auszulesen
*/

#include <EEPROM.h>

int add = 0;        //Momentane Adresse, ab welchem Byte gelesen wird (Arduino Uno max. 512 bytes)

void setup() {
    
    Serial.begin(9600);     //Starte Serial Monitor für die Anzeige der Variable

}

void loop() {

    setE1();      //Funktion ausführen
    byte val;       //Definiere die Variable val als Datentyp byte
    val = EEPROM.read(add);     //Sreibt den Inhalt des EEPROMs in die Variable val
    Serial.println(val);        //Gibt die ausgelesen Variable im Serial Monitor aus

    delay(1000);

}

void setE1() {      //Funktion um Variable im 1ten Byte des EEPROM zu speichern

    int val = 7;       //Test Variable gesetzt
    EEPROM.write(add, val);     //Speichere Variable auf EEPROM

}
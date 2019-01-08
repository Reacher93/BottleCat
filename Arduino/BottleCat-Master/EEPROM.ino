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
    byte val1;       //Definiere die Variable val1 als Datentyp byte
    val1 = EEPROM.read(add);     //Schreibt den Inhalt des 1ten Bytes des EEPROMs in die Variable
    Serial.println(val1);        //Gibt die ausgelesen Variable im Serial Monitor aus

    delay(1000);

    setE2();        //Funktion ausführen
    float val2;     //Definiere die Variable val2 als Datentyp float
    EEPROM.get(add, val2);     //Schreibt den Inhalt ab dem 2ten Byte des EEPROMs in die Variable
    Serial.println(val2);       //Gibt die ausgelesen Variable im Serial Monitor aus

    delay(1000);

}

void setE1() {      //Funktion um Variable im 1ten Byte des EEPROM zu speichern

    int val = 7;       //Test Variable gesetzt
    EEPROM.write(add, val);     //Speichere Variable auf EEPROM

}

void setE2() {      //Funktion um grössere Daten ab 2ten Byte zu speichern
    
    float val = 22.5;      //Test Variable setzen
    add = 1;     //Zum 2ten Byte springen für das speichern
    EEPROM.put(add, val);        //speichert val in EEPROM

}
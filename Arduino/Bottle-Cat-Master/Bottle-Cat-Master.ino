/*---Bottle Cat---
 * Arduino Programm zum steuern eines Flaschenöffner Roboters
 * 
 * Erstellt von:
 * Marcel Rankwiler und Damian Zahner
 * Am: 31.01.2019
 * 
 * Zusätzlich benötigte Files für die Anwendung sind:
 * - LCD-I2C.ino
 * - I2C-Temp.ino
 * - ZeitBerechnung_Temp-Flasche.ino
 * - Bluetooth-Master.ino
 * - Schrittmotormelodie.ino
 */

//Alle benötigten Libraries inkludieren
#include <Stepper.h>

//Definiere benötigte konstante Variablen
#define Pin_Mctrl 5 // Definition motor-disable pin

//Alle Globalen Variablen
float TB1 = 8;      //Deviniere Gemessene Flaschen Temp.
float TR = 22.5;    //Deviniere Gemessene Raump Temp.
float TB2 = 12;     //Definierte max. Flaschen Temperatur
int BtlHgh = 200;   //Flaschen Höhe in mm

Stepper Zaxis(200, 25, 18, 23, 33); // Steps / u, Pinout

void setup() {
  
  initI2C();    //Initalisiert die benötigten Schritte für die I2C Funktionen
  initBT();     //Initialisierung vom Bluetooth
  LCD_init();   //Initialisierung des LCDs
  
  //Setup für Stepper
  pinMode(0, INPUT);
  pinMode(Pin_Mctrl, OUTPUT);
  digitalWrite(Pin_Mctrl, HIGH);

  for(int i = 0; i <= 3; i++){    //Animation der Augen beim starten
  lcd_animation();
  }

  playsound();    //Melodie abspielen beim starten
}

void loop() {
TB1 = readTempBtl();   //Temp. Flasche einlesen
TR = readTempRoom();   //Temp. Raum einlesen
TR += 12;              //Offset für Raum temp. da die Board temp. Abweichungen hat
TB1 -= 2;              //Offset für Flaschen temp. da die Board temp. Abweichungen hat

lcd_loop();

  if(BTabfragen() == "StarteBC200"){

    if(TB1 > TB2){
      int zeit2;
      zeit2 = ZeitBk(TB1);    //Berechnung: Zeit zum kühlen 
      lcd_cooling(zeit2);
      }
    else{
        int zeit;
        zeit = ZeitBw(TB1, TR);   //Berechung: Zeit zum trinken
        lcd_drink(zeit);
        delay(5000);
      }
       //Bier öffnen folgt
       Bier_open();
       lcd_clear();     //LCD löschen für saubere lcd_loop Anzeige
    }
}

void Bier_open(){
  int steps = 0;
  steps = (284 - BtlHgh) * 50;   //284mm von der Grundplatte bis zum Öffnungspunkt, 50 Schritte/mm
  Zaxis.setSpeed(300);
  digitalWrite(Pin_Mctrl, LOW);
  Zaxis.step(steps);
  digitalWrite(Pin_Mctrl, HIGH);
  delay(250);
  digitalWrite(Pin_Mctrl, LOW);
  Zaxis.step(-steps);
  digitalWrite(Pin_Mctrl, HIGH);
}

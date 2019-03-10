/*---Bottle Cat---
 * Arduino Programm zum steuern eines Flaschenöffner Roboters
 * 
 * Erstellt von:
 * Marcel Rankwiler und Damian Zahner
 */

//Alle benötigten Libraries inkludieren
#include <LiquidCrystal_I2C.h>
#include <BluetoothSerial.h>    //Benötigte Library für die Serielle Bluetooth Übertragung mit dem ESP32 Modul
#include <Stepper.h>

//Alle Globalen Variablen
#define rx 25       //RX für Serielle Schnittstelle
#define tx 26       //TX für Serielle Schnittstelle
float TB1 = 8;      //Deviniere Gemessene Flaschen Temp.
float TR = 22.5;    //Deviniere Gemessene Raump Temp.
float TB2 = 10;     //Definierte max. Flaschen Temperatur
int pin_motor = 2;
int ref = 16;        //Pin Nummer für Referenzieren des Motors
int BtlHgh = 200;  //Flaschen Höhe in mm

//LCD init
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows); 

BluetoothSerial BT;   //Serialschnitstelle BT definiert

Stepper Zaxis(200, 25, 18, 23, 33); // Steps / u, Pinout

void setup() {
  
  initI2C();    //Initalisiert die benötigten Schritte für die I2C Funktionen
  initBT();     //Initialisierung vom Bluetooth

  //LCD init
  lcd.init();                    
  lcd.backlight();

  //Setup für Stepper
  pinMode(0, INPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  pinMode(pin_motor, OUTPUT);
  pinMode(ref, INPUT);

  //Motor referenzieren
  lcd.clear();
  lcd.print("Achtung Referenzierfahrt in:   s");
  for(int i = 10; i == 0; i--){
    lcd.setCursor(13, 1);
    lcd.print(i);
    delay(1000);
    }
    lcd.clear();
    lcd.print("Achtung Motor referenziert");
    refMotor();

  
}

void loop() {

  if(BTabfragen() == "StarteBC200"){
    //Flaschen Temperatur messen
    TB1 = readTemp();
    lcd.clear();
    lcd.print("Flasche hat");
    lcd.setCursor(0, 1);
    lcd.print(TB1);
    lcd.setCursor(4, 1);
    lcd.print("°C");

    //Zeitberechnung aus Sättigungsfunktion und Abklingfunktion mit Anzeige auf LCD
    if(TB1 > TB2){
      int zeit2;
      zeit2 = ZeitBk(TB1);
      lcd.clear();
      lcd.print("Bier ist zu warm!");
      delay(5000);
      lcd.clear();
      lcd.print(zeit2 / 60);
      lcd.setCursor(4, 0);
      lcd.println(" min kühl stellen");
      }
    else if(Voraussetzung(TB1, TR) == 0){
        lcd.clear();
        lcd.print("Fehler, bitte wiederholen");
      }
      else{
        int zeit;
        zeit = ZeitBw(TB1, TR);
        lcd.clear();
        lcd.print("Achtung, Bier wird geöffnet");

       //Bier öffnen folgt
       int steps = 0;
       steps = (280 - BtlHgh) * 50;   //280mm von der Grundplatte bis zum Öffnungspunkt, 50 Schritte/mm
       Zaxis.setSpeed(200);
       Zaxis.step(steps - 1000);
       Zaxis.setSpeed(50);
       Zaxis.step(1000);
       delay(250);
       Zaxis.setSpeed(200);
       Zaxis.step(-steps - 1000);
       Zaxis.setSpeed(200);
       Zaxis.step(-1000);

       lcd.clear();
       lcd.print("Bitte innerhalb von ");
       lcd.setCursor(1, 4);
       lcd.print(zeit / 60);
       lcd.setCursor(1, 8);
       lcd.print("min trinken");
      }
  }


 
}

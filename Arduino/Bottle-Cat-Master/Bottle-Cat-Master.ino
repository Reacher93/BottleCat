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

/*
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
*/

  for(int i = 0; i <= 3; i++){
  lcd_animation();
  }

  playsound();
}

void loop() {
TB1 = readTempBtl();   //Temp. Flasche einlesen
TR = readTempRoom();   //Temp. Raum einlesen
TR += 11;              //Offset für Raum temp.
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
       lcd.clear();     
    }
}

void lcd_animation(){   //Augen der Katze anzeigen
  lcd.clear();
  lcd.print(" 00        00");
  lcd.setCursor(0, 1);
  lcd.print(" 00        00");
  delay(1500);
  lcd.clear();
  lcd.print("   00        00");
  lcd.setCursor(0, 1);
  lcd.print("   00        00");
  delay(1500);
}

void lcd_loop(){    //Raum und Flaschen Temp. Anzeige
  lcd.setCursor(0, 0);
  lcd.print("Raum:    ");
  lcd.print(TR);
  lcd.print((char) 223);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print("Flasche: ");
  lcd.print(TB1);
  lcd.print((char) 223);
  lcd.print(" ");
}

void lcd_cooling(int zeit){    //Anzeige zu kühlstellende Zeit
  lcd.clear();
  lcd.print("Rat der Katze:");
  lcd.setCursor(0, 1);
  lcd.print(zeit);
  lcd.print(" min k");
  lcd.print("\365");
  lcd.print("hlen");
}

void lcd_drink(int zeit){    //Anzeige Zeit zum trinken
  lcd.clear();
  lcd.print("Rat der Katze");
  lcd.setCursor(0, 1);
  lcd.print("Trinken in ");
  lcd.print(zeit);
  lcd.print(" min");
}

void Bier_open(){
  int steps = 0;
  steps = (284 - BtlHgh) * 50;   //284mm von der Grundplatte bis zum Öffnungspunkt, 50 Schritte/mm
  Zaxis.setSpeed(300);
  digitalWrite(5, LOW);
  Zaxis.step(steps);
  digitalWrite(5, HIGH);
  delay(250);
  digitalWrite(5, LOW);
  Zaxis.step(-steps);
  digitalWrite(5, HIGH);
}

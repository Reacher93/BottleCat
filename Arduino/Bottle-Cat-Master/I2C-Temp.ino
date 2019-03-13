//Gehört zum Master Sketch; Bottle-Cat

#include <Wire.h>           //Benötigte Datenbank für I2C Kommunikation

#define TempAdd 0x40        //Temperatursensor I2C Hex Address
#define TempO 0x03          //Interne Adresse für Objekt Temperatur
#define TempR 0x01          //Interne Adresse Board Temp. für Raum Temp.

void initI2C(){
  Wire.begin();             //Starte I2C Kommunikation
  }

float readTempBtl(void)                   //Funktion für das Auslesen der Temperatur
{
  float Temp;                               //Variable für Objekt Temperatur
  
  Wire.beginTransmission(TempAdd);        //Starte Kommunikation zum Temperatursensor
  Wire.write(TempO);                      //Abfrage der Objekt Temperatur
      
  Wire.endTransmission();                 //Beendet die Kommunikation

  Wire.requestFrom(TempAdd,1);            //Abfrage der übertragenen Daten von den zwei Limit Temperaturen

  if(Wire.available()<=1){                //Nachfragen ob die zwei passenden Daten verfügbar sind und in die ensprechenden Varianlen einlesen (OT)
    Temp = Wire.read();
    }
    return(Temp);
}

float readTempRoom(void)                  //Funktion für das Auslesen der Board Temperatur
{
  float Temp;                             //Variable für Board Temperatur
  
  Wire.beginTransmission(TempAdd);        //Starte Kommunikation zum Temperatursensor
  Wire.write(TempR);                      //Abfrage der Board Temperatur
      
  Wire.endTransmission();                 //Beendet die Kommunikation

  Wire.requestFrom(TempAdd,1);            //Abfrage der übertragenen Daten von den zwei Limit Temperaturen

  if(Wire.available()<=1){                //Nachfragen ob die zwei passenden Daten verfügbar sind und in die ensprechenden Varianlen einlesen (OT)
    Temp = Wire.read();
    }
    return(Temp);
}

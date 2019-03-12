#include <math.h>

float ZK = 6000;    //Ermittelte Zeitkonstate für Sättigungsfunktion (Flaschenaufwärmung)
float ZK2 = 5000;   //Ermittelte Zeitkonstate für Abklingfunktion (Flasche kühlen)
//float TB2 = 9;    //Definierte max. Flaschen Temperatur
float TK = 3;   //Kühlschrank Temperatur
float TB3 = 7;    //Soll Temperatur Flasche aus Kühlschrank

int ZeitBw(float TB1, float TR){   //Funktion zur Berechnung der Zeit (in sec.), bis die Flasche die max. Temperatur erreicht
  int zeit;
  zeit = log(TR/(TB1-TB2+TR))*ZK;
  zeit = zeit / 60;   //Umrechnung in min
  return zeit;
}


int ZeitBk(float TB1){
  int zeit;
  zeit = log(TB1/(TB3-TK))*ZK2;
  zeit = zeit / 60;   //Umrechnung in min
  return zeit;
}

/*
void setup() {
  Serial.begin(9600);
 
}

void loop() {
  
  float TB1 = 11;   //Gemessene Flaschen Temp.
  float TR = 22.5;    //Gemessene Raump Temp.
  int zeit = 0;   //Definiere Zeit für Aufwärmung
  int zeit2 = 0;    //Definiere Zeit 2 für Abkühlen
  
  if(TB1 > TB2){
    zeit2 = ZeitBk(TB1);
    Serial.print("Bier ist zu warm, bitte ");
    Serial.print(zeit2);
    Serial.println(" sec. kühl stellen");
  }
  else if(Voraussetzung(TB1, TR) == 0){
    Serial.println("Berechnung nicht möglich, bitte Temperaturen neu messen");
  }
  else{
    zeit = ZeitBw(TB1, TR);
    Serial.println(zeit);
  }
  delay(10000);
}
*/

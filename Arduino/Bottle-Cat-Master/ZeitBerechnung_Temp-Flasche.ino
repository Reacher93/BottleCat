//Gehört zum Master Sketch; Bottle-Cat

#include <math.h>   //Datenbank für Berechnungen notwendig

#define ZK 6690     //Ermittelte Zeitkonstate für Sättigungsfunktion (Flaschenaufwärmung)
#define ZK2 6690    //Zeitkonstate für Abklingfunktion (Flasche kühlen) Annahme, dass selbe Konstante gilt

float TK = 3;       //Kühlschrank Temperatur, globale Variable bereit für evtl. eingbe per Smartphone
float TB3 = 7;      //Soll Temperatur Flasche aus Kühlschrank, globale Variable bereit für evtl. eingbe per Smartphone

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

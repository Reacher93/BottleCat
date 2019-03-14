//Gehört zum Master Sketch; Bottle-Cat

#include <math.h>   //Datenbank für Berechnungen notwendig

#define ZK 2529     //Ermittelte Zeitkonstate (in sec) für Sättigungsfunktion (Flaschenaufwärmung)
#define ZK2 2529    //Zeitkonstate (in sec) für Abklingfunktion (Flasche kühlen) Annahme, dass selbe Konstante gilt

float TK = 4;       //Kühlschrank Temperatur, globale Variable bereit für evtl. eingbe per Smartphone
float TB3 = 8;      //Soll Temperatur Flasche aus Kühlschrank, globale Variable bereit für evtl. eingbe per Smartphone

int ZeitBw(float TB1, float TR){   //Funktion zur Berechnung der Zeit (in sec.), bis die Flasche die max. Temperatur erreicht
  int zeit;
  zeit = ZK*log((TR-TB1)/(TR-TB2));
  zeit = zeit / 60;   //Umrechnung in min
  return zeit;
}

int ZeitBk(float TB1){
  int zeit;
  zeit = ZK2*log((TB1-TK)/(TB3-TK));
  zeit = zeit / 60;   //Umrechnung in min
  return zeit;
}


#include <Stepper.h>
// #ifndef myTypes_h
#define myTypes_h
//#include <WString.h>

/*
//LCD init
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows); 
*/

 int bottletemp;
 //int testvar;
 //int pulse = 0;


int amps1 = 0;
int amps2 = 0;
float pitchshifter = 3;
float timeshifter = 3;

int sechzentel = 125;
int achtel = 250;
int viertel = 500;
// int notenzahl = 18;

#define Tone_C5 523.251
#define Tone_A4 440.000
#define Tone_B4 466.164
#define Tone_C4 261.626
#define Tone_D4 293.665
#define Tone_E4 329.628
#define Tone_Fis4 369.994
#define Tone_G4 391.995
#define Tone_A3 220.000
#define Tone_B3 246.942
#define Tone_G3 195.998

typedef struct song_wwwt
{
  int pitch;
  int lenght;
};
song_wwwt waswollenwirtrinken[] = {
{ Tone_D4, achtel }, { Tone_D4, achtel }, { Tone_B3, achtel }, { Tone_C4, viertel }, { Tone_A3, viertel },
{ Tone_A3, achtel }, { Tone_D4, achtel }, { Tone_D4, achtel }, { Tone_C4, achtel }, { Tone_B3, achtel },
{ Tone_D4, achtel }, { Tone_D4, achtel }, { Tone_B3, achtel }, { Tone_C4, viertel }, { Tone_A3, viertel },
{ Tone_B3, achtel }, { Tone_G3, achtel }, { Tone_A3, viertel }
};

//Stepper Zaxis(200, 25, 18, 23, 33); // Steps / u, Pinout

void refMotor(){    //Motor referenzieren
  Zaxis.setSpeed(80);    //Speed reduziert, da Referenzfahrt Stromüberwacht stoppt
  while(ref == LOW){
    Zaxis.step(-1000);    //5400 Stepps -> 27 Umdrehungen -> 111mm Verfahrweg
  }
}
  
  
void playsound() {
    
 //Serial.println(sizeof(song_wwwt) + 10);
  //delay(3000);
  for (int i = 0; i < 18; i++)
  {
  Zaxis.setSpeed(waswollenwirtrinken[i].pitch * pitchshifter);
  digitalWrite(5, LOW);
  Zaxis.step(waswollenwirtrinken[i].lenght * timeshifter);
 // Serial.println(analogRead(34));
  digitalWrite(5, HIGH);
  
 delay(30);
  }
    
}

/*
void setup()
{

}

void loop()
{
 
}
*/

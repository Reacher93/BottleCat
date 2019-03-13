//Gehört zum Master Sketch; Bottle-Cat

#include <Stepper.h>

#define myTypes_h

// Definition der Notenlänge
#define timeshifter 3 //Multiplikator der Tonlänge
#define achtel  250
#define viertel  500
#define notenzahl 18

// Definition der Tonhöhe
#define pitchshifter 3 // Multiplikator der Tonhöhe
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

// In diesem Struct sind die Informationen der Melodie enthalten
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

// Funktion, um die Melodie vom Struct abzuspielen
void playsound() 
{
  for (int i = 0; i < notenzahl; i++)
  {
  Zaxis.setSpeed(waswollenwirtrinken[i].pitch * pitchshifter);
  digitalWrite(Pin_Mctrl, LOW);
  Zaxis.step(waswollenwirtrinken[i].lenght * timeshifter);
  digitalWrite(Pin_Mctrl, HIGH);
  delay(30);
  }  
}

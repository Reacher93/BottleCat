#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
// #ifndef myTypes_h
#define myTypes_h
#include <WString.h>
#include <D:\Bottlecat\BottleCat\ESP32\BC_Wifi_Stabile02.ino\index.htm>

//LCD init
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows); 

WebServer server; // Serverobjekt erstellen
WebSocketsServer webSocket = WebSocketsServer(81);
uint8_t pin_led = 16;
char* ssid = "FRITZ!Box Fon WLAN 7390";
char* password = "9997637707206775";

// char* ssid = "iPhone";
// char* password = "testtest";

// char* ssid = "GallusMobile";
// char* password = "20GALLwLan13!!5";




 int pin_motor = 2;
 int bottletemp;
 int testvar;
 int pulse = 0;
 char tx_to_brower[100]; 
 String rx_from_brower;   


int amps1 = 0;
int amps2 = 0;

float pitchshifter = 0.8;
float timeshifter = 0.8;

int sechzentel = 125;
int achtel = 250;
int viertel = 500;
// int notenzahl = 18;

float Tone_C5 = 523.251;
float Tone_A4 = 440.000;
float Tone_B4 = 466.164;
float Tone_C4 = 261.626;
float Tone_D4 = 293.665;
float Tone_E4 = 329.628;
float Tone_Fis4 = 369.994;
float Tone_G4 = 391.995;
float Tone_A3 = 220.000;
float Tone_B3 = 246.942;
float Tone_G3 = 195.998;

//char lied[] = "waswollenwirtrinken";
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
/*
typedef struct song_wwwt1 
{
  int pitch;
  int lenght;
};
song_wwwt1 waswollenwirtrinken1[] = {
{ Tone_D4, viertel }, { Tone_D4, -sechzentel }, { Tone_C4, achtel }, { Tone_B4, achtel }, { Tone_C4, viertel },
{ Tone_C4, viertel }, { Tone_A4, achtel }, { Tone_D4, achtel }, { Tone_D4, achtel }, { Tone_C4, achtel },
{ Tone_B4, achtel }, { Tone_D4, achtel }, { Tone_D4, -sechzentel }, { Tone_C4, achtel }, { Tone_B4, achtel },
{ Tone_C4, viertel }, { Tone_A4, viertel }, { Tone_B4, achtel }, { Tone_G4, achtel }, { Tone_A4, viertel }
};

typedef struct song_wwwt2 
{
  int pitch;
  int lenght;
};
song_wwwt2 waswollenwirtrinken2[] = {
{ Tone_E4, -viertel }, { Tone_G4, -achtel }, { Tone_A4, -achtel }, { Tone_B4, -viertel }, { Tone_B4, -viertel },
{ Tone_C5, -achtel }, { Tone_A4, -achtel }, { Tone_B4, -viertel }, { Tone_A4, -viertel }, { Tone_A4, -sechzentel },
{ Tone_G4, -sechzentel }, { Tone_Fis4, -achtel }, { Tone_G4, -viertel }, { Tone_E4, viertel }, { Tone_E4, -achtel },
{ Tone_A4, -achtel }, { Tone_A4, -achtel }, { Tone_G4, -achtel }, { Tone_Fis4, -achtel }, { Tone_A4, -achtel },
{ Tone_A4, sechzentel }, { Tone_G4, -achtel }, { Tone_Fis4, achtel }, { Tone_G4, viertel }, { Tone_E4, -viertel }, 
{ Tone_Fis4, -achtel }, { Tone_D4, -achtel }, { Tone_E4, viertel }
};
*/
Stepper Zaxis(200, 25, 18, 23, 33); // Steps / u, Pinout

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
    for (int i = 0; i < 18; i++)
  {
  Zaxis.setSpeed(waswollenwirtrinken[i].pitch * pitchshifter);
  digitalWrite(5, LOW);
  Zaxis.step(-waswollenwirtrinken[i].lenght * timeshifter);
 // Serial.println(analogRead(34));
  digitalWrite(5, HIGH);
  
  // delay(5);
  }
  }

void setup()
{
  pinMode(0, INPUT);
pinMode(5, OUTPUT);
digitalWrite(5, HIGH);
  pinMode(pin_motor, OUTPUT);
  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){
    server.send_P(200, "text/html", webpage); 
  //  server.send_P(200, "text/html", watchdog); //pleaes reset aus handy - code, content type, content   
  /*  
  String message ? "File Not Found\n\n";
  https://www.youtube.com/watch?v=BJkliQ9jORw
  15:31 min:sec
  
  server.send(404, "text/plain", message);
  */
  });
  server.begin();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop()
{
bottletemp = millis()/1000;
testvar = millis()/2000;
updatews();
  webSocket.loop(); // evtl mit internem timer-interrupt ansteuern
  server.handleClient(); // schaut nach webserver aktivität

//LCD
lcd.init();                    
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print(WiFi.localIP());
  
}


void updatews(){
   
sprintf(tx_to_brower, "%d, %d", bottletemp, testvar);
webSocket.broadcastTXT(tx_to_brower);   
// server.send(200, "
  
  }

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){ 
    rx_from_brower = "";
   for(int i = 0; i < length; i++){
   // rx_from_brower = (rx_from_brower.concat((char) payload[i]));
   rx_from_brower += (char)payload[i];
    }
    Serial.println(rx_from_brower);
     
     if(payload[0] == '+'){
      uint16_t rxtemperatur = (uint16_t) strtol((const char *) &payload[1], NULL, 10);
      bottletemp = rxtemperatur; // zum löschen nach Sensoranschluss
      Serial.print("Temperatur= ");
      Serial.println(bottletemp);
    }
     else if(rx_from_brower == "StartMachine"){
      webSocket.broadcastTXT("d");
      Serial.print("Sende Temperatur= ");
     // Serial.println(blinkdelay);
      Serial.println(bottletemp);
     // String btemp = String((char*) bottletemp);
     // Serial.println(btemp);
    //  webSocket.broadcastTXT(tmp);
      Serial.println("Starte Maschine");
      delay(2000);
      playsound();
      Serial.println("Ende");
      webSocket.broadcastTXT("e");
    }
  else  if(rx_from_brower == "ToggleLed"){
 //analogWrite(pin_led, 1024);
 digitalWrite(pin_motor, 1);
 delay(20);
 digitalWrite(pin_motor, 0);
 // analogWrite(pin_led, 1);
  Serial.println("Toggle durchgeführt");
    } 
 else  if(rx_from_brower == "MotorSpin"){
   Serial.println("Spin start");
   
 for(int i = 0; i < 500; i++){
 digitalWrite(pin_motor, 1);
 digitalWrite(pin_motor, 0);
 delay(2);
        }
        
        delay(50);
        
 for(int i = 0; i < 500; i++){
 digitalWrite(pin_motor, 1);
 digitalWrite(pin_motor, 0);
 delay(2);
        }
        
        delay(50);
        
 for(int i = 0; i < 500; i++){
 digitalWrite(pin_motor, 1);
 digitalWrite(pin_motor, 0);
 delay(2);
        }
 delay(2.5);
 
  for(int i = 0; i < 1000; i++){
 digitalWrite(pin_motor, 1);
  digitalWrite(pin_motor, 0);
 delay(2);
        }
        
        
        
        

 /*               for(int i = 0; i < 200; i++){
 digitalWrite(pin_motor, 1);
  digitalWrite(pin_motor, 0);
 delay(2);
        }
                for(int i = 0; i < 200; i++){
 digitalWrite(pin_motor, 1);
  digitalWrite(pin_motor, 0);
 delay(4);
        }
                for(int i = 0; i < 400; i++){
 digitalWrite(pin_motor, 1);
  digitalWrite(pin_motor, 0);
 delay(2);
        } */
  Serial.println("Spin durchgeführt");
    } 
  }
}

#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> // Speziell für ESP32
//#include <WString.h>

//Server-HTML Datei, wird in Flash Memory gespeichert
#include <D:\ZbW\BottleCat\Arduino\Testfiles\I-Sense_ESP32_Wifi.ino\index.htm>

//Include für ESP32 Energiemanagement
#include <esp_pm.h>
#include <esp_wifi_types.h>
#include <esp_wifi.h>

// #define myTypes_h

//Variabeln für Strom Messeingänge
#define sense2 33
#define sense4 39

//Ausgang, wenn Maximalstrom erriecht
#define MaxCurrentReached 5

// Ausgang für Motor Disable
#define MotCtrl 5 


// Ausgang für DC-Servo
#define Servo_Pin 21 

//Internes LED
#define intern_led 13 

//GND für Display / VCC ist an 5V von BC
#define LCD_GND 14 

//Variabeln um den Maximalstrom zu bestimmen
int inow1 = 0;
int inow2 = 0;
int imax1 = 0;
int imax2 = 0;

// Zeitstempel für Maximalstrom-Speicher (CurrnetPeak)
int TimeStamp = 0; 

// Variable für die Systemzeit (Einschaltdauer) umgerechnet in Sekunden
int ontime = 0; 


// Servoobjekt erstellen
Servo CatTail; 

// Serverobjekt erstellen
WebServer server; 

// WebSocket Server starten
WebSocketsServer webSocket = WebSocketsServer(81);


// char* ssid = "FRITZ!Box Fon WLAN 7390";
// char* password = "9997637707206775";

// char* ssid = "iPhone";
// char* password = "testtest";

char* ssid = "GallusMobile";
char* password = "20GALLwLan13!!5";

//char* ssid ="test";
//char * password = "testtest";





// Variabeln für Endgeräte Kommunikation
 char tx_to_brower[50]; //Text, der an den Browser gesendet wird
 String rx_from_brower;  //Text, der vom Browser empfangen wird







// Funktion, welche den Datenaustausch zwischen Server und Client (Endgerät) aktualisiert
void updatews(){  
sprintf(tx_to_brower, "%d, %d, %d, %d, %d", ontime, inow1, inow2, imax1, imax2);
webSocket.broadcastTXT(tx_to_brower); }

// Event-Handler

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){ 
    rx_from_brower = "";
   for(int i = 0; i < length; i++){
   rx_from_brower += (char)payload[i]; //Ladet die einzelnen Buchstaben vom WS in einen Char-Array
    }
     if(rx_from_brower == "wedeln"){ //Funktion wedeln
      webSocket.broadcastTXT("d");
      wedeln();
      webSocket.broadcastTXT("e"); 
      }
      else  if(rx_from_brower == "torqueon"){
      Serial.println("Torque On");
      digitalWrite(intern_led, HIGH);
      digitalWrite(MotCtrl, LOW);
       } 
      else  if(rx_from_brower == "torqueoff"){ 
      Serial.println("Torque OFF");
      digitalWrite(MotCtrl, HIGH);
      digitalWrite(intern_led, LOW);
      }
    }
}


void setup()
{
  //Motor-Anschluss deaktivieren / hochohmig schalten
  pinMode(MotCtrl, OUTPUT);
  digitalWrite(MotCtrl, HIGH);

  //Ground schalten für LCD, damit die Pins nebeneinander sind
  pinMode(LCD_GND, OUTPUT);
  digitalWrite(LCD_GND, LOW);

  //Analog Eingang an sense2 / 4 zuweisen für ESP32
  adcAttachPin(sense2);
  adcAttachPin(sense4);

  //Maximalstrom Ausgang definieren
  pinMode(MaxCurrentReached, OUTPUT);

  //LED Ausgang definieren
  pinMode(intern_led, OUTPUT);
  digitalWrite(intern_led, LOW);

  //Serielle Schnittstelle initialisieren
  Serial.begin(115200);

  //Pin an Servo zuweisen
  CatTail.attach(Servo_Pin);

  //Servo in Grundposition fahren
  CatTail.write(120);
  
 //LCD init // Display initialisieren
 LiquidCrystal_I2C lcd(0x3F, 16, 2); //Displayobjekt erstellen (Adresse, anzahl Spalten, anzahl Zeilen)



  //Wifi Energienanagement
  WiFi.mode (WIFI_STA); // Powermodus
  esp_wifi_set_ps (WIFI_PS_NONE); // Energiesparmodus beenden <- Grund wenn ESP32 Wifi langsam läuft
  

  //Mit Wifi AP verbinden
  WiFi.begin(ssid,password);

  //Warten bis verbunden
  while(WiFi.status()!=WL_CONNECTED)
  {
    //Serial.print(".");
    delay(500);
  }
  digitalWrite(intern_led, HIGH);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

//Wird gesendet, wenn mit Client (Endgerät) verbunden
  server.on("/",[](){
    server.send_P(200, "text/html", webpage); 
  });

// Webserver starten
  server.begin();

// Websocket Echtzeitverbindung starten
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

// LCD Display initialisieren
lcd.init();                    
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print(WiFi.localIP());
}

// Funktion schwanz wedeln inkl. Beschleunigungsrampe

void wedeln(){
      Serial.println("Wedeln");
      for (int i = 1; i <= 50; i++) {
      CatTail.write(120+i);          // Position auf Pin schreiben
      if(i > 30){ 
      delay (5+(i-30)); 
      } 
      else {
      delay (20-(0.5*i));              // 10° / sec ,Wartezeit zwischen den nächsten Step
      }
      }

      for (int i = 1; i <= 50; i++) {
      CatTail.write(170-i);          // Position auf Pin schreiben
      if(i > 30){ 
      delay (5+(i-30)); 
      } 
      else {
      delay (20-(0.5*i));              // 10° / sec ,Wartezeit zwischen den nächsten Step
      }
      }

      /*
      for (int i = 1; i <= 60; i++) {
      CatTail.write(170-i);
      delay (35-(0.5*i)); // 10° / sec
      }
  */
  }

void loop()
{
 ontime = millis()/1000; // Speichert die aktuelle Systemlaufzeit in Sekunden
 inow1 = analogRead(sense2);
 inow2 = analogRead(sense4);

 //Erkennung für Maximalstrom
if (inow1 < 4000 || inow2 < 4000){ 
  digitalWrite(MotCtrl, HIGH);
  TimeStamp = millis(); // Zeitstämpel setzen
  }
if (imax1 < inow1){ imax1 = inow1; } // Maximalstrom in Variable speichern
if (imax2 < inow2){ imax2 = inow2; }
updatews(); // Sendet die neuen Variabeln zum Websocket
webSocket.loop(); // 
server.handleClient(); // schaut nach webserver aktivität

if (TimeStamp + 3000 < millis()){ digitalWrite(MotCtrl, LOW); } //Motorausgang freigeben, falls Überstrom nach 3 Sekunden nicht mehr vorhanden
 
}

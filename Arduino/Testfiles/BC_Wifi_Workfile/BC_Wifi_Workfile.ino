#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>


ESP8266WebServer server;
WebSocketsServer webSocket = WebSocketsServer(81);
uint8_t pin_led = 16;
char* ssid = "FRITZ!Box Fon WLAN 7390";
char* password = "9997637707206775";

char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <style type="text/css">
   
  .text { 
    
    font-size: 18px;
    color:red;
    } 
  p {
  box-sizing: border-box;
  width: 60%
  border-width: 10px;
  border-color: black;
  border-style: solid;
  float: center;
  }
  body {
    background-color: #F8F8F8;
    padding: 10px 0px 10px 10px;
    margin: 0px;
    }
  
  
  </style>
<title>Bottle Cat 0.1</title>
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <script>

    var Socket;
    function init() 
     {
      Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
      Socket.onmessage = function(event)
       {
       if (event.data == "e")
        { 
        document.getElementById("start").disabled = false; 
        }
       else if (event.data == "d")
        { 
        document.getElementById("start").disabled = true; 
        }
       else 
        {
       var str = event.data;
       var tagsArray = str.split(",");
       document.getElementById("aaa").value = tagsArray[0];   
       document.getElementById("bbb").value = tagsArray[1]; 
       document.getElementById("ddd").value = str; 
       document.getElementById("slider").value = parseInt(tagsArray[0]);                   
        } 

     }
     }
 
     function ledtoggle(){
      Socket.send("ToggleLed");
    } 
           
   function motorspin(){
      Socket.send("MotorSpin");
    } 
   function test(){
      Socket.send("12345");
    } 
     function start(){
      Socket.send("StartMachine")      
    }   
  </script>

</head>
<body onload="javascript:init()">
 <p> <span class="text"> BottleCat v0.1 </span></br> 
  </br>
  <div>
  <input id="slider" type="range" min="1" max="300"/>
  </div>
  </br>
  <div>
    Temperatur 1: <output type="text" id="bbb"/>
  </div></br>
 <div>
    Temperatur 2: <output type="text" id="aaa"/>
  </div>
      <hr/>
       <div>
    String-Value: <output type="text" id="ddd"/>
  </div>
      <hr/>
    <div>
 <center>  <button id="start" onclick="start()" style="height: 100px; width: 200px;">Start Maschine</button></center>
  </div>
      <div>
  <center> <button id="ledbut" onclick="motorspin()" style="height: 100px; width: 200px;">Motor Spin</button></center>
  </div>
        <div>
  <center> <button id="ledbut" onclick="ledtoggle()" style="height: 100px; width: 200px;">LED Toggle</button></center>
  </div>
        <div>
  <center> <button onclick="test()" style="height: 100px; width: 200px;">Testfunktion</button></center>
  </div></p>
</body>
</html>
)=====";
 int pin_motor = 2;
 int bottletemp;
 int testvar;
 int pulse = 0;
 char tx_to_brower[100]; 
 String rx_from_brower;   

void setup()
{
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
  server.handleClient();
}


void updatews(){
   
sprintf(tx_to_brower, "%d, %d", bottletemp, testvar);
webSocket.broadcastTXT(tx_to_brower);   
  
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
      Serial.println("Ende");
      webSocket.broadcastTXT("e");
    }
  else  if(rx_from_brower == "ToggleLed"){
 analogWrite(pin_led, 1024);
 digitalWrite(pin_motor, 1);
 delay(20);
 digitalWrite(pin_motor, 0);
  analogWrite(pin_led, 1);
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
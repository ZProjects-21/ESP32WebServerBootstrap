#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SD.h>
#include <FS.h>
#include <SPI.h>

/* ------------------------- setup ssid and password ------------------------ */
const char* ssid("SSID");           //input your ssid here 
const char* password("PASSWORD");   //input your password here 

/* --------------------------- Change your ip here -------------------------- */
IPAddress local_IP(192,168,32,32);  //ipv4  
IPAddress gateway(192,168,32,32);   //your gateway
IPAddress subnet(255,255,255,0);
IPAddress dns1(1,1,1,2);            //(optional)
IPAddress dns2(1,0,0,2);            //(optional)

AsyncWebServer server(80);

/* ---------------------------------- setup --------------------------------- */
void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  // Configure ip
  if(!WiFi.config(local_IP,gateway,subnet,dns1,dns2)){ //you can empty the dns1, and dns2
    Serial.println("Static ip fail confugure");
  }
    Serial.println("Static ip confugure");

  while (WiFi.status()== WL_DISCONNECTED)
  {
    Serial.print("Connecting");
    delay(500);
  }
  Serial.print("Connected to : ");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.subnetMask());
  Serial.println(WiFi.dnsIP(1));
  Serial.println(WiFi.dnsIP(2));


  // initialize SD Card
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
    }

  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/html/index.html", "text/html");
  });
  
  server.on("/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/css/bootstrap.min.css", "text/css");
  });
  
  server.on("/bootstrap.min.js",HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/js/bootstrap.min.js", "application/js");
  });
  
  server.begin();
}

/* ---------------------------------- loop ---------------------------------- */
void loop(){

}
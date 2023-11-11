#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Ping.h>
#include <BleKeyboard.h>


#include "html.h"
#include "privatedata.h"
#include <cstring>

BleKeyboard bleKeyboard;
String receivedChars;

String receivedSymbol;

IPAddress Actual_IP;

IPAddress PageIP(172, 20, 10, 1);
IPAddress gateway(172, 20, 10, 1);
IPAddress subnetm(255, 255, 255, 0);
IPAddress ip;

//const char* ssid = WIFI_SSID;
//const char* password = WIFI_PASS;

int fail_count = 0;
int local_or_public = 3;
WebServer server(80);
WiFiClient client;


void AP_();
void show_network_data();
void label();
void pint_test();

String ip_a;
String sm;
String ip_g;

void setup() {
  Serial.begin(115200);
  label();
  disableCore0WDT();
  //  disableCore1WDT()

  bleKeyboard.setName(BLUETOOTH_NAME);
  Serial.print("Bluetooth name . . . . . : ");
  Serial.println(BLUETOOTH_NAME);
  bleKeyboard.begin();
  
  WiFi.setHostname(AP_SSID);
  Serial.print("Set hostname . . . . . . : "); Serial.println(WiFi.getHostname());
  Serial.print("Connecting to. . . . . . : "); Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    if (fail_count > 20){
      
      break;
      }
    delay(500);
    Serial.print(".");
    fail_count++;
  }
  Serial.println("");
  if(WiFi.status()!= WL_CONNECTED){
      WiFi.disconnect();
      AP_();
      ip_a = WiFi.softAPIP().toString();
      sm = subnetm.toString();
      ip_g = WiFi.softAPIP().toString();
      local_or_public = 0;
    }
   else {
      Serial.println("WiFi connected");
      local_or_public = 1;
      ip_a = WiFi.localIP().toString();
      sm = WiFi.subnetMask().toString();
      ip_g = WiFi.gatewayIP().toString();
    }
    
  show_network_data(ip_a,sm,ip_g);
  if (local_or_public == 1){
    ping_test();
  }
  Serial.println("");
  Serial.print("Web server started . . . : ");
  Serial.println(ip_a);
  Serial.println(""); 
  
  // Define routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/symbol", HTTP_GET, handleSymbol);
  
  server.begin();
  
}

void loop() {
  server.handleClient();
}

void handleRoot() {
//    new_client();
    server.send(200, "text/html", PAGE_MAIN); 
}

void handleSymbol() {
    if (server.hasArg("symbol")) {
        receivedSymbol = server.arg("symbol");
        Serial.println(receivedSymbol);
        
        if (receivedSymbol == "ENTER" || receivedSymbol == "enter") {
            bleKeyboard.write(KEY_RETURN);
        } else if (receivedSymbol == "<<") {
            bleKeyboard.write(KEY_BACKSPACE);
        } else if (receivedSymbol == "SPACE" || receivedSymbol == "space") {
            bleKeyboard.print(" ");
        } else {
            bleKeyboard.print(receivedSymbol);
        }
    }


//    new_client();
    server.send(200, "text/plain", "Symbol received");
}


void new_client() {
    client = server.client();
    Serial.print("New client connected . . : ");
    Serial.print(client.remoteIP());
    Serial.print(":");
    Serial.println(client.remotePort());
}



void AP_(){
    Serial.println("Failed to connect to network");
    Serial.println("");
    Serial.println("Access Point Created");
    Serial.print("SSID . . . . . . . . . . : "); Serial.println(AP_SSID);
    Serial.print("PASSWORD . . . . . . . . : "); Serial.println(AP_PASS);
    Serial.println("");
    WiFi.softAP(AP_SSID, AP_PASS);
    delay(100);
    WiFi.softAPConfig(PageIP, gateway, subnetm);
    delay(100);
  }

void label(){
  Serial.println("= = = = = = = = = = = = = =");
  Serial.println("= =  Designed By Nesa   = =");
  Serial.println("= = = = = = = = = = = = = =");
  
  }

void show_network_data(String Data1, String Data2, String Data3){
  Serial.print("IP address . . . . . . . : ");
  Serial.println(Data1);
  Serial.print("Subnet Mask. . . . . . . : ");
  Serial.println(Data2);
  Serial.print("Gateway IP address . . . : ");
  Serial.println(Data3);
  long rssi = WiFi.RSSI();
  Serial.print("RSSI . . . . . . . . . . : "); Serial.print(rssi); Serial.println(" dBm");
  return;
  }
void ping_test(){
  Serial.print("Test ping www.google.com : ");
    bool success = Ping.ping("www.google.com", 3);
    if(!success){
    Serial.println("FAILED");
    return;
    }
    else{
      Serial.println("PASS");
    }
  }

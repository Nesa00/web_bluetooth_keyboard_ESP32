#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ESP32Ping.h>
#include <BleKeyboard.h>

#include "html.h"
#include <cstring>

//#define USE_INTRANET

BleKeyboard bleKeyboard;

String receivedChars;
//char receivedChars[100]; // Array to store received characters
int currentIndex = 0;


#define AP_SSID "AP NAME"
#define AP_PASS "AP PASSWORD"

char XML[2048];
char buf[32];
String header;
String receivedSymbol;

IPAddress Actual_IP;

IPAddress PageIP(172, 20, 10, 1);
IPAddress gateway(172, 20, 10, 1);
IPAddress subnetm(255, 255, 255, 0);
IPAddress ip;

// Replace with your network credentials
const char* ssid = "YOUR LOCAL WIFI SSID";
const char* password = "YOUR LOCAL WIFI PASSWORD";

int fail_count = 0;
int local_or_public = 3;
bool LED0 = false, SomeOutput = false;
uint32_t SensorUpdate = 0;

WebServer server(80);
WiFiClient client;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;


String hostname = "HOSTNAME";

void AP_();
void show_network_data();
void label();
void pint_test();

String ip_a;
String sm;
String ip_g;

void setup() {
  Serial.begin(115200);
//  label();

  disableCore0WDT();
  //  disableCore1WDT()


  bleKeyboard.setName("KEYBOARD NAME");
  Serial.println("Bluetooth name: KEYBOARD NAME");
  
  bleKeyboard.begin();
  
  WiFi.setHostname(hostname.c_str());
  Serial.print("Set hostname . . . . . . : "); Serial.println(WiFi.getHostname());
  Serial.print("Connecting to. . . . . . : "); Serial.println(ssid);
  WiFi.begin(ssid, password);
  
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

    new_client();
    server.send(200, "text/html", PAGE_MAIN); 
}

void handleSymbol() {
    // Get the symbol from the query parameter
    if (server.hasArg("symbol")) {
        receivedSymbol = server.arg("symbol");
//        Serial.print("Received symbol: ");
        Serial.print(receivedSymbol);
        bleKeyboard.print(receivedSymbol);
    }
    new_client();
    // Send a response back to the client
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

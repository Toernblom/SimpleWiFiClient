#include "Arduino.h"
#include "SimpleWiFiClient.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>



SimpleWiFiClient::SimpleWiFiClient() {
 
  

}

void SimpleWiFiClient::init(char* ssid, char* password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  wifi_set_sleep_type(NONE_SLEEP_T);
  Udp.begin(localUdpPort);
  ip = WiFi.localIP().toString().c_str();
}
void SimpleWiFiClient::run() {
  int packetSize = Udp.parsePacket();
  
  if (packetSize)
  {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = '\0';
    }
    message = (String) incomingPacket;
    handleInputs(message);
  }

}

void SimpleWiFiClient::handleInputs(String message) {
    
    if(input(message) == "vertical") {
      vertical = message.substring(1).toFloat();
    } 
    
    if(input(message) == "horizontal"){
      horizontal = message.substring(1).toFloat();
    }
    
    if(input(message) == "button1") {
      button1 = asBool(message.substring(1).toInt());
    }
    if(input(message) == "button2") {
      button2 = asBool(message.substring(1).toInt());
    }
    if(input(message) == "button3") {
      button2 = asBool(message.substring(1).toInt());
    }

}
bool SimpleWiFiClient::asBool(int x) {
  bool b = false;
  if(x >= 1) b = true;
  return b;
}
String SimpleWiFiClient::input(String message) {
  String s = "";
  switch(message.substring(0,1).toInt()) {
    case 0: s = "horizontal";
    break;
    case 1: s = "vertical";
    break;
    case 2: s = "button1";
    break;
    case 3: s = "button2";
    break;
    case 4: s = "button3";
  }
  return s;
}

void SimpleWiFiClient::invoke(String message) {
  action(message);
}

void SimpleWiFiClient::attach(m_cb act) {
  action = act;
}
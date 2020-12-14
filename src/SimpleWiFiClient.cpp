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
    invoke(message);
  }

}

void SimpleWiFiClient::invoke(String message) {
  action(message);
}

void SimpleWiFiClient::attach(m_cb act) {
  action = act;
}
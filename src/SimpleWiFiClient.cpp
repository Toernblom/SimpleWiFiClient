#include "Arduino.h"
#include "SimpleWiFiClient.h"

#if defined(ARDUINO_SAMD_NANO_33_IOT)
#include <WiFiNINA.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <WiFiUdp.h>

SimpleWiFiClient::SimpleWiFiClient()
{
}

void SimpleWiFiClient::init(char *ssid, char *password)
{
#if defined(ESP8266)
  WiFi.mode(WIFI_STA);
#endif

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
#if defined(ESP8266)
  wifi_set_sleep_type(NONE_SLEEP_T);
#endif
  Udp.begin(localUdpPort);
  ip = WiFi.localIP();
}

void SimpleWiFiClient::run()
{
  int packetSize = Udp.parsePacket();

  if (packetSize)
  {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = '\0';
    }
    message = (String)incomingPacket;
    invoke(message);
  }
}

void SimpleWiFiClient::invoke(String message)
{
  action(message);
}

void SimpleWiFiClient::attach(m_cb act)
{
  action = act;
}
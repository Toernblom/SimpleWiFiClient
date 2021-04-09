#include "Arduino.h"
#include <WiFiUdp.h>

class SimpleWiFiClient
{
  using m_cb = void (*)(String);
  public:
    SimpleWiFiClient();
    void init(char* ssid, char* password);
    void run();
    void attach(m_cb act);
    void invoke(String message);
    IPAddress ip;
  private:
    String message; 
    m_cb action;
    const char* ssid;
    const char* password;
    WiFiUDP Udp;
    unsigned int localUdpPort = 4210;
    char incomingPacket[256];
};
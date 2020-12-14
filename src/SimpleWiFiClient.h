#include "Arduino.h"
#include <WiFiUdp.h>

class SimpleWiFiClient
{
  using m_cb = void (*)(String);
  public:
    SimpleWiFiClient();
    void init(char* ssid, char* password);
    float horizontal;
    float vertical;
    bool button1;
    bool button2;
    bool button3;
    bool button4;
    void run();
    void attach(m_cb act);
    void invoke(String message);
    String ip;
  private:
    void handleInputs(String message);
    String input(String message);
    bool asBool(int x);
    String message; 
    m_cb action;
    const char* ssid;
    const char* password;
    WiFiUDP Udp;
    unsigned int localUdpPort = 4210;
    char incomingPacket[256];
};
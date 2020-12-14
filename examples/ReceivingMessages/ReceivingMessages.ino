#include <SimpleWiFiClient.h>

// Instance of object
SimpleWiFiClient simpleWiFiClient;

void setup() {
  Serial.begin(9600);

  // Connects to WiFi and initializes UDP to listen on port 4210
  simpleWiFiClient.init("ssid","password");

  // Attaches SimpleWiFiClient to send the recieved message 
  // from port 4210 to the method, in this case, OnRecieved.
  simpleWiFiClient.attach(OnRecieved);
}

// Message recieved as a string.
void OnRecieved(String message) {
  Serial.println(message);
}

void loop() {
  // Listens for incomming messages then invokes the
  // action to send the message to the attached method.
  simpleWiFiClient.run();

}

# SimpleWiFiClient
 A simple low latency UDP arduino client.

## Version 0.5.0

Initial beta release.

## Intro



#### Compatible hardware

- ESP8266

- Soon ESP32, Arduino nano 33 IOT.




#### Installation

Make sure to have compatible hardware board installed.

1. Download the latest release from src.
2. Install through Arduino IDE.



## How to - Arduino

#### Include and create instance
```
include <SimpleWiFiClient.h>
SimpleWiFiClient simpleWiFiClient;
```


#### Setup

```
simpleWiFiClient.init("ssid","password");
simpleWiFiClient.attach(OnRecieved);
```

```
void OnRecieved(String message) {
  Serial.println(message);
}
```

#### Loop

```
simpleWiFiClient.run();
```

## Send data

### Use UDP and send the packet as bytes.

#### In python

```python
import socket

message = bytes("Hello, World!", "utf-8")
socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
socket.sendto(message, ("192.168.1.83", 4210))
```
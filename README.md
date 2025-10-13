# OrbiterGateway
Firmware for photo sensor gateway to server

## Hardware
Reference used for this project: `ESP32-C3-DevKitM-1 v1.6`

## Installation
Once the repository is cloned:

1. Create a `main/include/wifi_credentials.h` file and add your wifi credentials
```C
#ifndef WIFI_CREDENTIALS_H
#define WIFI_CREDENTIALS_H

// Add your Wifi credentials here
#define ESP_WIFI_SSID "XXX"
#define ESP_WIFI_PASS "XXX"

#endif // WIFI_CREDENTIALS_H

```
2. Execute the following command to avoid mistakenly sharing your credentials
```sh
git config core.hooksPath .githooks
```

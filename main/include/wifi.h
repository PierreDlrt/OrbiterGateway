#ifndef WIFI_H
#define WIFI_H

#include "esp_system.h"

void wifi_init_sta(esp_err_t (* onConnected)(void));

#endif // WIFI_H

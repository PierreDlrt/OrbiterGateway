#ifndef MQTT_H
#define MQTT_H

#include "mqtt_client.h"

void mqtt_app_init(void);

esp_err_t mqtt_send(const char *topic, const char *data, int len, int qos);

#endif // MQTT_H

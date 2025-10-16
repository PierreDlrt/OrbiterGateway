/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "esp_log.h"
#include "nvs_flash.h"
#include "blecent.h"
#include "utils.h"
#include "wifi.h"
#include "mqtt.h"

#if CONFIG_EXAMPLE_USE_CI_ADDRESS
#ifdef CONFIG_IDF_TARGET_ESP32
#define TEST_CI_ADDRESS_CHIP_OFFSET (0)
#elif CONFIG_IDF_TARGET_ESP32C2
#define TEST_CI_ADDRESS_CHIP_OFFSET (1)
#elif CONFIG_IDF_TARGET_ESP32C3
#define TEST_CI_ADDRESS_CHIP_OFFSET (2)
#elif CONFIG_IDF_TARGET_ESP32C6
#define TEST_CI_ADDRESS_CHIP_OFFSET (3)
#elif CONFIG_IDF_TARGET_ESP32C5
#define TEST_CI_ADDRESS_CHIP_OFFSET (4)
#elif CONFIG_IDF_TARGET_ESP32H2
#define TEST_CI_ADDRESS_CHIP_OFFSET (5)
#elif CONFIG_IDF_TARGET_ESP32P4
#define TEST_CI_ADDRESS_CHIP_OFFSET (6)
#elif CONFIG_IDF_TARGET_ESP32S3
#define TEST_CI_ADDRESS_CHIP_OFFSET (7)
#elif CONFIG_IDF_TARGET_ESP32C61
#define TEST_CI_ADDRESS_CHIP_OFFSET (8)
#endif
#endif

static const char *TAG = "MAIN";

#define APP_BANNER()                                                       \
    do                                                                     \
    {                                                                      \
        ESP_LOGI(TAG, "------------------------------------------------"); \
        ESP_LOGI(TAG, "_______       ______ __________             ");     \
        ESP_LOGI(TAG, "__  __ \\_________  /____(_)_  /_____________");    \
        ESP_LOGI(TAG, "_  / / /_  ___/_  __ \\_  /_  __/  _ \\_  ___/");   \
        ESP_LOGI(TAG, "/ /_/ /_  /   _  /_/ /  / / /_ /  __/  /    ");     \
        ESP_LOGI(TAG, "\\____/ /_/    /_.___//_/  \\__/ \\___//_/     ");  \
        ESP_LOGI(TAG, "------------------------------------------------"); \
    } while (0)

static void forwardToServer(uint8_t device_id, time_t timestamp, uint8_t *data, uint8_t len)
{
    char payload[128];
    char topic[32];
    char time_buf[64];
    struct tm timeinfo;

    if (len == 4)
    {
        memset(payload, 0, sizeof payload);

        // Build json
        snprintf(payload, sizeof payload, "{");
        if (((uint16_t *)data)[0] != 0)
        {
            snprintf(payload + strlen(payload), sizeof payload - strlen(payload),
                     "\"V1k\": %u, ", ((uint16_t *)data)[0]);
        }
        if (((uint16_t *)data)[1] != 0)
        {
            snprintf(payload + strlen(payload), sizeof payload - strlen(payload),
                     "\"V10k\": %u, ", ((uint16_t *)data)[1]);
        }
        snprintf(payload + strlen(payload), sizeof payload - strlen(payload),
                 "\"timestamp\": %lld}", timestamp);

        // Get time for log
        localtime_r(&timestamp, &timeinfo);
        strftime(time_buf, 64, "%F %T", &timeinfo);
        snprintf(topic, sizeof topic, "sensors/" SENSOR_NAME_SUF "%u", device_id);

        // Send to MQTT
        mqtt_send(topic, payload, strlen(payload), 1);

        ESP_LOGI(TAG, "[%s] Publish %s on %s", time_buf, payload, topic);
    }
}

void app_main(void)
{
    /* Initialize NVS — it is used to store PHY calibration data */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    APP_BANNER();

    wifi_init_sta(init_datetime);

    mqtt_app_init();

    ble_cent_init(forwardToServer);
}

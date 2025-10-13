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

void forwardToServer(uint8_t device_id, uint8_t *data, uint8_t len)
{
    print_time();

    if (len == 4)
    {
        printf("From " SENSOR_NAME_SUF "%u: Rchan2 = %f, Rchan3 = %f\n", device_id,
               (float)((uint16_t *)data)[0],
               (float)((uint16_t *)data)[1]);
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

    ble_cent_init(forwardToServer);
}

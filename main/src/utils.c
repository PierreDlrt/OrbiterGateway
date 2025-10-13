#include "utils.h"
#include "esp_sntp.h"
#include "esp_netif_sntp.h"
#include "esp_log.h"

static const char *TAG = "UTILS";

void print_byte(uint8_t *bytes, int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        printf("0x%02x ", bytes[i]);
    }
    putchar('\n');
}

void get_time(char *time_buf, uint8_t size)
{
    time_t now;
    struct tm timeinfo;

    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(time_buf, size, "%F %T", &timeinfo);
}

void print_time(void)
{
    char strftime_buf[64];

    get_time(strftime_buf, sizeof strftime_buf);
    printf("[%s] \n", strftime_buf);
}

esp_err_t init_datetime(void)
{
    esp_err_t ret;
    int retry = 0;
    const int retry_count = 15;
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");

    ret = esp_netif_sntp_init(&config);
    while (esp_netif_sntp_sync_wait(2000 / portTICK_PERIOD_MS) == ESP_ERR_TIMEOUT && ++retry < retry_count)
    {
        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
    }

    // Set timezone to Central European Time with daylight saving time
    setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);
    tzset();

    ESP_LOGI(TAG, "Time set");
    print_time();

    return ret;
}

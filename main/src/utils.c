#include "utils.h"
#include "esp_sntp.h"

void print_byte(uint8_t *bytes, int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        printf("0x%02x ", bytes[i]);
    }
    putchar('\n');
}

void print_time(void)
{
    time_t now;
    char strftime_buf[64];
    struct tm timeinfo;

    time(&now);
    // Set timezone to Central Europe Time
    setenv("TZ", "CET-1", 1);
    tzset();

    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    printf("[%s] \n", strftime_buf);
}

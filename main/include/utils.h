#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "esp_system.h"
#include "esp_sntp.h"

void print_byte(uint8_t *bytes, int len);
esp_err_t init_datetime(void);
void print_time(void);
void get_time(char *time_buf, uint8_t size);

#endif // UTILS_H

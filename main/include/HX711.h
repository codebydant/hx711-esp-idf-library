#include "hx711_lib.h"
#include <inttypes.h>

#include "esp32/clk.h"
#include "esp32/rom/rtc.h"
#include "esp_attr.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_intr_alloc.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_sntp.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "esp_task.h"
#include "esp_timer.h"
#include "esp_tls.h"
#include "esp_wifi.h"

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "nvs_flash.h"

#include <tcpip_adapter.h>

#include <sys/time.h>
#include <time.h>

#include "sdkconfig.h"
#include "soc/apb_ctrl_reg.h"
#include "soc/dport_reg.h"
#include "soc/efuse_periph.h"
#include "soc/frc_timer_reg.h"
#include "soc/rtc.h"
#include "soc/rtc_periph.h"
#include "soc/sens_periph.h"
#include "xtensa/core-macros.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

esp_err_t read_hx711();
int32_t get_average_reading(int num_average);
long read_rw();
uint8_t shiftIn2(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
void setGain(int gain);
bool readyToSend();
long read_average(int times);
double get_value(int times);
float get_units(int times);
long get_offset();
void set_offset(long offset);
float get_scale();
void set_scale(float scale);
void tare(int times);
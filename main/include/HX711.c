#include "HX711.h"
#include "hx711_lib.h"
#define HIGH 1
#define LOW 0

bool pinsConfigured;
int LSBFIRST = 0;
int MSBFIRST = 1;

int PD_SCK;      // Power Down and Serial Clock Input Pin
int DOUT;        // Serial Data Output Pin
int GAIN;        // amplification factor
long OFFSET = 0; // used for tare weight
float SCALE = 1; // used to return weight in grams, kg, ounces, whatever

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 33;
const int LOADCELL_SCK_PIN = 32;
int CLOCK_PIN = LOADCELL_SCK_PIN;
int OUT_PIN = LOADCELL_DOUT_PIN;

static hx711_t *scale;

esp_err_t read_hx711() {

  printf("~~~~~~~~~~~~~~~~~\n");
  printf("  HX711 Sensor   \n");
  printf("~~~~~~~~~~~~~~~~~\n");
  printf("-> setting HX711 options\n");

  scale = malloc(sizeof(*scale));
  scale->dout = LOADCELL_DOUT_PIN;
  scale->pd_sck = LOADCELL_SCK_PIN;

  hx711_gain_t gain_hx711 = {0};

  printf("-> setting loadcell dout pin %d \n", scale->dout);
  printf("-> setting loadcell sck pin %d \n", scale->pd_sck);

  hx711_init(scale);
  hx711_set_gain(scale, gain_hx711);

  bool stt = false;

  bool *ready = &stt;
  int init_pointer = 0;
  int32_t *raw_data = &init_pointer;

  printf("-> reading data...\n");
  esp_err_t status = hx711_is_ready(scale, ready);

  // Loop
  while (status == ESP_OK) {
    // while (1) {

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Setup led status = RED
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (*ready) {

      status = hx711_read_data(scale, raw_data);
      printf("-> raw data: %" PRId32 "\n", *raw_data);

      // int32_t avr = get_average_reading(5);
      long avr = read_average(5);
      printf("-> average of (5): %ld\n", avr);

      avr = read_average(20);
      printf("-> average of (20): %ld\n", avr);

      float units = get_units(5);
      printf("-> units before calibration: %.2f\n", units);

      set_scale(233.82); // this value is obtained by calibrating the
                         // scale with known weights
      tare(1);           // reset the scale to 0

      units = get_units(5);
      printf("-> units after calibration: %.2f\n", units);

      // vTaskDelay(1000 / portTICK_PERIOD_MS);
      break;

    } else {

      printf("-> HX711 is not ready\n");
      vTaskDelay(500 / portTICK_PERIOD_MS);
      size_t timeout_ms = 1000;
      status = hx711_wait(scale, timeout_ms);
      status = hx711_is_ready(scale, ready);
    }
  }

  if (status == ESP_FAIL) {
    printf("-> could't read data\n");
    return ESP_FAIL;
  } else {
    printf("\n");
    return ESP_OK;
  }
}

int32_t get_average_reading(int num_average) {

  esp_err_t status;
  int init_pointer = 0;
  int32_t *raw_data = &init_pointer;

  int32_t sum = 0;
  int32_t average = 0;

  for (int i = 0; i < num_average; i++) {
    status = hx711_read_data(scale, raw_data);
    if (status == ESP_OK) {
      sum += *raw_data;
    }
  }
  average = (int32_t)(sum / num_average);
  return average;
}

long read_average(int times) {
  long sum = 0;
  for (int i = 0; i < times; i++) {
    sum += read_rw();
    // Probably will do no harm on AVR but will feed the Watchdog Timer (WDT) on
    // ESP.
    // https://github.com/bogde/HX711/issues/73
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
  return sum / times;
}

double get_value(int times) { return read_average(times) - OFFSET; }

float get_units(int times) { return get_value(times) / SCALE; }

void tare(int times) {
  double sum = read_average(times);
  set_offset(sum);
}

void set_scale(float scale) { SCALE = scale; }

float get_scale() { return SCALE; }

void set_offset(long offset) { OFFSET = offset; }

long get_offset() { return OFFSET; }

bool readyToSend() {
  if (!pinsConfigured) {
    // We need to set the pin mode once, but not in the constructor
    gpio_set_direction(CLOCK_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(OUT_PIN, GPIO_MODE_INPUT);
    pinsConfigured = true;
  }
  return gpio_get_level(OUT_PIN) == LOW;
}

void setGain(int gain) {
  switch (gain) {
  case 128:
    GAIN = 1;
    break;
  case 64:
    GAIN = 3;
    break;
  case 32:
    GAIN = 2;
    break;
  }

  gpio_set_level(CLOCK_PIN, LOW);
  read_rw();
}

uint8_t shiftIn2(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {

  uint8_t value = 0;
  uint8_t i;

  for (i = 0; i < 8; ++i) {

    gpio_set_level(clockPin, HIGH);

    if (bitOrder == LSBFIRST) {
      value |= gpio_get_level(dataPin) << i;
    } else {
      value |= gpio_get_level(dataPin) << (7 - i);
    }
    gpio_set_level(clockPin, LOW);
  }
  return value;
}

long read_rw() {
  while (!readyToSend())
    ;

  int data[3];

  for (int j = 3; j--;) {
    data[j] = shiftIn2(OUT_PIN, CLOCK_PIN, MSBFIRST);
  }

  // set gain
  for (int i = 0; i < GAIN; i++) {
    gpio_set_level(CLOCK_PIN, HIGH);
    gpio_set_level(CLOCK_PIN, LOW);
  }

  data[2] ^= 0x80;
  return ((uint32_t)data[2] << 16) | ((uint32_t)data[1] << 8) | (uint32_t)data[0];
}
//***************** Program *****************************
#include "include/HX711.h"
#include "sdkconfig.h"

//***************** Main program ************************
void app_main(void) {

  // Setting clang format on Sublime text3:
  // https://xiaoyuliu.github.io/2018/03/30/20180330-clang-format/

  printf("\n");
  printf("*** MAIN PROGRAM ***\n");
  printf("\n");

  // Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  esp_err_t status = ESP_FAIL;

  while (status != ESP_OK) {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Read HX711 data
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    status = read_hx711();
  }
}
//***************** End main program ************************

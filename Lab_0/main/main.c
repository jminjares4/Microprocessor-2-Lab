#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BLINK_GPIO 5
void app_main(void)
{
    gpio_reset_pin(BLINK_GPIO);

    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    // gpio_set_pull_mode(BLINK_GPIO, GPIO_PULLDOWN_ONLY);
    while(1){
        printf("Turning  on LED...\n");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_RATE_MS);

        printf("Turning off LED...\n");
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

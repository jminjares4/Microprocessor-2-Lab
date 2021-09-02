/*
    Author: Jesus Minjares
            Master of Science in Computer Engineering
    Date:   09-02-2021
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define BLINK_GPIO 5
void app_main(void)
{
    /*REset the GPIO pin*/
    gpio_reset_pin(BLINK_GPIO);
    /*Set the direction of the GPIO as OUTPUT*/
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while(1){
        /*Turn on the LED*/
        printf("Turning  on LED...\n");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_RATE_MS);

        /*Turn off the LED*/
        printf("Turning off LED...\n");
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

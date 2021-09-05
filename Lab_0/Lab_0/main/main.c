/*
    Author:     Jesus Minjares
                Master of Science in Computer Engineering
    Course:     EE 5190 Laboratory for Microprocessors Systems II        
    Lab 0:
                Lab 0 goals is to provide exposure of freeRTOS. It task
                was to run the given code and modify additional features 
                of the bonus. The code will print to the screen every second 
                "Hello world!" and turn off and on the LED for 2 and 3 second respectively.
    Date:       09-05-2021
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

/*Define pin 13 as a "BLINK_GPIO*/
#define BLINK_GPIO 13

/*Code for the hello_task task*/
void hello_task(void *pvParameter){
    while(1){
        /*print to the screen and de;ay this task by 100ms*/
        print("Hello world!\n");
        /*Modify the code so that your program prints to the screen every one second,*/
        // vTaskDelay(100 / portTICK_RATE_MS);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
/*Code for the blinky task*/
void blinky(void *pvParameter){
    /* Define pin 13 as a GPIO and make it an OUTPUT */
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_select_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1){
        /*the LED is off for two seconds and on for three seconds*/
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(2000 / portTICK_RATE_MS);
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(3000 / portTICK_RATE_MS);
    }
}
void app_main(){
    /*Create the task defined by xTaskCreate, NULL is used to specify "not required"*/
    xTaskCreate(&hello_task, "hello_task", 2048, NULL, 5, NULL );
    xTaskCreate(&blinky, "blinky", 2048, NULL, 5, NULL );
}
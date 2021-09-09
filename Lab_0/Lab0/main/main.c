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

    Pinout:

                                         +-----------------------+
                                         | O      | USB |      O |
                                         |        -------        |
                                     3V3 | [ ]               [ ] | VIN
                                     GND | [ ]               [ ] | GND
     Touch3 / HSPI_CS0 / ADC2_3 / GPIO15 | [ ]               [ ] | GPIO13 / ADC2_4 / HSPI_ID / Touch4
 CS / Touch2 / HSPI_WP / ADC2_2 /  GPIO2 | [ ]               [ ] | GPIO12 / ADC2_5 / HSPI_Q / Touch5
      Touch0 / HSPI_HD / ADC2_0 /  GPIO4 | [ ]               [ ] | GPIO14 / ADC2_6 / HSPI_CLK / Touch6
                         U2_RXD / GPIO16 | [ ]               [ ] | GPIO27 / ADC2_7 / Touch7
                         U2_TXD / GPIO17 | [ ]               [ ] | GPIO26 / ADC2_9 / DAC2
                      V_SPI_CS0 /  GPIO5 | [ ]  ___________  [ ] | GPIO25 / ADC2_8 / DAC1
                SCK / V_SPI_CLK / GPIO18 | [ ] |           | [ ] | GPIO33 / ADC1_5 / Touch8 / XTAL32
        U0_CTS / MSIO / V_SPI_Q / GPIO19 | [ ] |           | [ ] | GPIO32 / ADC1_4 / Touch9 / XTAL32
                 SDA / V_SPI_HD / GPIO21 | [ ] |           | [ ] | GPIO35 / ADC1_7 
                  CLK2 / U0_RXD /  GPIO3 | [ ] |           | [ ] | GPIO34 / ADC1_6 
                  CLK3 / U0_TXD /  GPIO1 | [ ] |           | [ ] | GPIO39 / ADC1_3 / SensVN 
        SCL / U0_RTS / V_SPI_WP / GPIO22 | [ ] |           | [ ] | GPIO36 / ADC1_0 / SensVP 
                MOSI / V_SPI_WP / GPIO23 | [ ] |___________| [ ] | EN 
                                         |                       |
                                         |  |  |  ____  ____  |  |
                                         |  |  |  |  |  |  |  |  |
                                         |  |__|__|  |__|  |__|  |
                                         | O                   O |
                                         +-----------------------+
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

/*Define pin 13 as a "BLINK_GPIO*/
#define BLINK_GPIO 2 //ONBOARD LED

/*Code for the hello_task task*/
void hello_task(void *pvParameter){
    while(1){
        /*print to the screen and de;ay this task by 100ms*/
        printf("Hello world!\n");
        /*Modify the code so that your program prints to the screen every one second,*/
        // vTaskDelay(100 / portTICK_RATE_MS);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
/*Code for the blinky task*/
void blinky(void *pvParameter){
    /* Define pin 13 as a GPIO and make it an OUTPUT */
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
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
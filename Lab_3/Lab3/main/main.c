/*
    Author:     Jesus Minjares
                Master of Science in Computer Engineering
    Course:     EE 5190 Laboratory for Microprocessors Systems II
    Lab 3:      The purpose of Lab 3 is to use the LEDC driver with ADC driver
                to control the duty cycle of the GPIO. Additionally, an port interrupt
                is added to stop and resume the timer of the pwm signal of the driver.
                
    Date:       10-07-2021
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
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <driver/ledc.h>
#include <driver/adc.h>
#include <driver/gpio.h>

#define ONBOARD_LED 2               //ONBOARD GPIO LED
#define BUTTON                  22  //GPIO22
#define GPIO_INPUT_SEL          1ULL << BUTTON //set GPIO select for INPUT 
#define ESP_INTR_FLAG_DEFAULT   0   //INTERRUPT DEFAULT FLAG
static xQueueHandle duty_queue = NULL; //global queue handle 

/*GPIO ISR Routine*/
static void IRAM_ATTR gpio_isr_handler(void * arg){

}
/* ADC Task*/
void ADCtask(void *pvParameter){
    while(1){
    }
}
/* PWM Task*/
void PWMtask(void *pvParameter){
    int val; //variable to store queue 
    while(1){

    }
}
/* Set ADC */
void setADC(){

}
/* Set PWM */
void setPWM(){
    
    ledc_timer_config_t timerConfig;
  
    ledc_timer_config(&timerConfig);
 
    ledc_channel_config_t tChaConfig;

    ledc_channel_config(&tChaConfig);
}
/* Set GPIO */
void setGPIO(){
 
}
/* main */
void app_main(void){
    /* set ADC | PWM | GPIO */
    setADC();
    setPWM();
    setGPIO();
    /* Create queue int[10] */
    duty_queue = xQueueCreate(10,sizeof(int));
    /* Create Tasks */
    xTaskCreate(&ADCtask, "ADCtask", 2048,NULL, 5, NULL);
    xTaskCreate(&PWMtask, "PWMtask", 2048, NULL, 5, NULL);
}

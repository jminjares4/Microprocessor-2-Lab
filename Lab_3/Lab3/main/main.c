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
    /*create a static variable to be store in static memory */
    static int count = 0;
    count++; //increment count 
    if(count == 1){ //check if 1
        ledc_timer_pause(LEDC_LOW_SPEED_MODE,LEDC_TIMER_0); //pause timer 
    }
    if(count == 2){ //check if 2
      ledc_timer_resume(LEDC_LOW_SPEED_MODE,LEDC_TIMER_0);  //stop timer
      count = 0; //reset count 
    }
}
/* ADC Task*/
void ADCtask(void *pvParameter){
    while(1){
        //every 100ms
        vTaskDelay(100/portTICK_PERIOD_MS);
        /*Read adc value @ CHANNEL 6*/
        int val = adc1_get_raw(ADC1_CHANNEL_6);   
        /*Send to queue*/
        xQueueSendToBack(duty_queue,&val,(TickType_t)10);
    }
}
/* PWM Task*/
void PWMtask(void *pvParameter){
    int val; //variable to store queue 
    while(1){
        if(xQueueReceive(duty_queue,&val,(TickType_t)10) == pdPASS){ //wait for queueu to recieve 
            printf("Val: %d\n", val); //display message 
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0,(uint32_t)val); //set duty 
            ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0); //update duty 
        } 
    }
}
/* Set ADC */
void setADC(){
    /*Set the ADC with @ 12 bits -> 2^12 = 4096*/
    adc1_config_width(ADC_WIDTH_BIT_12);
    /*Set CHANNEL 6 @ 2600 mV*/
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
}
/* Set PWM */
void setPWM(){
    /*
        Set LEDC Timer:
                        5000hz
                        AUTO_CLK
                        TIMER_0
                        LOW_SPEED
                        13 BIT
    */
    ledc_timer_config_t timerConfig;
    timerConfig.duty_resolution = LEDC_TIMER_13_BIT; 
    timerConfig.timer_num = LEDC_TIMER_0;
    timerConfig.freq_hz = 5000; 
    timerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    timerConfig.clk_cfg = LEDC_AUTO_CLK;
    ledc_timer_config(&timerConfig);
    /*
        Set LEDC Channel:
                        GPIO_2
                        LOW_SPEED
                        TIMER_0
                        LOW_SPEED
                        0 duty
    */
    ledc_channel_config_t tChaConfig;
    tChaConfig.gpio_num = ONBOARD_LED;    
    tChaConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    tChaConfig.channel = LEDC_CHANNEL_0;
    tChaConfig.intr_type = LEDC_INTR_DISABLE;
    tChaConfig.timer_sel = LEDC_TIMER_0 ;
    tChaConfig.duty = 0;
    ledc_channel_config(&tChaConfig);
}
/* Set GPIO */
void setGPIO(){
    /*
        GPIO config:
                        INPUT
                        PULL_UP
                        NEG_EDGE
                        GPIO_2
    */
    gpio_config_t io;
    io.pin_bit_mask = GPIO_INPUT_SEL;
    io.mode = GPIO_MODE_INPUT;
    io.pull_down_en = 0;
    io.pull_up_en = 1;
    io.intr_type = GPIO_INTR_NEGEDGE;

    /* set configuration */
    gpio_config(&io);
    /* Set IRS @ 0 to non-share memory */
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    /* Attach BUTTON @ gpio isr */
    gpio_isr_handler_add(BUTTON, gpio_isr_handler, (void*)NULL);
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

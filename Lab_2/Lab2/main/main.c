/*
    Author:     Jesus Minjares
                Master of Science in Computer Engineering
    Course:     EE 5190 Laboratory for Microprocessors Systems II

    Lab 2:      The purpose of Lab 2 is to get familiar with interrupts
                on ESP32 microcontroller. The lab consist of triggering an
                interrupt by an external push buttons that will display an
                message via serial terminal. Every time the interrupt is trigger
                it will toggle the onboard led to provide visual representation of
                the interrupt occuring. 
                
    Date:       09-30-2021
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
#include "driver/gpio.h"

/* MACROs for external buttons */
#define GPIO_BUTTON_0 21
#define GPIO_BUTTON_1 22
#define GPIO_BUTTON_2 23

/*  ULL is an 8 bytes data type and the GPIO pins need to 
    be set to ULL because gpio_config_t pin_bit_mask is an uint64_t. 
    The pin_bit_mask is 8 bytes long therefore the GPIO has to be set to the
    corresponding data type by using left bit shift 
*/
#define GPIO_INPUT_SEL (1ULL << GPIO_BUTTON_0 | 1ULL << GPIO_BUTTON_1 | 1ULL << GPIO_BUTTON_2)

/* Input MACROs */
#define ONBOARD_LED 2
#define GPIO_OUTPUT_SEL (1ULL << ONBOARD_LED)

/*  Set INTR_FLAG to 0 */
#define ESP_INTR_FLAG_DEFAULT 0

/* Create an static queue and intialize to NULL */
static xQueueHandle gpio_queue = NULL;

/* GPIO interrupt */
static void IRAM_ATTR gpio_isr_handler(void * arg){
    uint32_t gpio_num = (uint32_t) arg; // store argument into gpio_num 
    GPIO.out ^= BIT2; //toggle LED
    /* Send gpio_num to the queue */
    xQueueSendFromISR(gpio_queue, (void *)&gpio_num, NULL);
}

/* This task will be trigger by the interrupt */
static void print_task(void *arg){
    uint32_t gpio_num; // store queue
    while(1){
        /* Wait until the queue recieves from ISR*/
        if(xQueueReceive(gpio_queue, (void *)&gpio_num, portMAX_DELAY)){
             //display what port number trigger the interrupt 
            printf("GPIO[%d] caused an interrupt\n", gpio_num);
        }
    }
}
/* GPIO setup */
void setUpGPIO(){
    gpio_config_t io_conf; // gpio_config_t is an data structure in driver/gpio
    /* INPUT */ 
    io_conf.intr_type = GPIO_INTR_NEGEDGE; // set as POSEDGE for interrupt 
    io_conf.mode = GPIO_MODE_INPUT; // set input 
    io_conf.pin_bit_mask = GPIO_INPUT_SEL; // set gpio that will be used for input 
    io_conf.pull_down_en = 0;  // disable pull down 
    io_conf.pull_up_en = 1;  // enable pull up 

    gpio_config(&io_conf); // set configuration 
    /* OUTPUT */
    io_conf.intr_type = GPIO_INTR_DISABLE; // disable interrupt 
    io_conf.mode = GPIO_MODE_OUTPUT; // set as output 
    io_conf.pin_bit_mask = GPIO_OUTPUT_SEL; // set gpio that will be used for output 
    io_conf.pull_down_en = 0 ; // disable pull down 
    io_conf.pull_up_en = 0; // disable pull up 

    gpio_config(&io_conf); // set configuration

    /*  Set ISR to non-share memory 
        If this value is 0, it will default to allocating
        a non-shared interrupt of level 1, 2 or 3.
    */
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    /* Attached GPIO interrupt to interrupt routine and pass an argument */
    gpio_isr_handler_add(GPIO_BUTTON_0, gpio_isr_handler, (void *)GPIO_BUTTON_0);
    gpio_isr_handler_add(GPIO_BUTTON_1, gpio_isr_handler, (void *)GPIO_BUTTON_1);
    gpio_isr_handler_add(GPIO_BUTTON_2, gpio_isr_handler, (void *)GPIO_BUTTON_2);
}

void app_main(void){
    /* Initialize GPIOs and Interrupt */
   setUpGPIO();
   /* Create an Queue of uint32-t [10] */
   gpio_queue = xQueueCreate(10, sizeof(uint32_t));
   /* Create task that will be trigger by interrupt */
   xTaskCreate(&print_task, "print_task", 2048, NULL, 10, NULL);
}

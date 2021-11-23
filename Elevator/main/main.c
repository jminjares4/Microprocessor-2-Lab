/* UART Echo Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "sdkconfig.h"
#include <string.h>
#include "esp_log.h"

// ESP32

// --Sensors--
// Accerlometer
// motion sensor
// ?

// --Hardware--
// SG90 Servo
// LEDs
// Buttons
// Resistors
// External Header Pins / UART  DONE!!!!

/* Set ADC */
void setADC(){
    /*Set the ADC with @ 12 bits -> 2^12 = 4096*/
    adc1_config_width(ADC_WIDTH_BIT_12);
    /*Set CHANNEL 6 @ 2600 mV*/
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11); 
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11); 
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); 

}

void adc_test(void *pvParameter){
    while(1){
         vTaskDelay(100/portTICK_PERIOD_MS);
        /*Read adc value @ CHANNEL 6*/
        printf("-----------------\n");
        int adc1 = adc1_get_raw(ADC1_CHANNEL_0);
        int adc2 = adc1_get_raw(ADC1_CHANNEL_3); 
        int adc3 = adc1_get_raw(ADC1_CHANNEL_6);    

        printf("ADC1: %d\nADC2: %d\nADC3: %d\n", adc1,adc2,adc3);
        printf("-----------------\n");

    }
}
#if 0
#define GPIO_BUTTON_0 21
#define GPIO_BUTTON_1 22
#define GPIO_BUTTON_2 23
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
static void task2(void *arg){
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

#define UART_2_TX 17
#define UART_2_RX 16
#define UART_BUFFER_SIZE 1024
const uart_port_t uart_num = UART_NUM_2;
void uart_setup(void)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
        uart_config_t uart_config = {
        .baud_rate = 9600,                     // defualt buadrate
        .data_bits = UART_DATA_8_BITS,         // 8 bits
        .parity = UART_PARITY_DISABLE,         // disable parity
        .stop_bits = UART_STOP_BITS_1,         // 1 stop bit
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, // disable hardware flow control
        .source_clk = UART_SCLK_APB,           // set default clock
    };
    // Initialize uart configuration @ uart_num
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    // Set uart pins for UART0
    ESP_ERROR_CHECK(uart_set_pin(uart_num, UART_2_TX, UART_2_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    // Install uart driver with a BUFFER * 2 size
    ESP_ERROR_CHECK(uart_driver_install(uart_num, UART_BUFFER_SIZE * 2, UART_BUFFER_SIZE * 2, 0, NULL, 0));
}

void task5(void *arg)
{
    const uart_port_t uart_num = UART_NUM_2;
    while (1)
    {
        // Write data to UART.
        char *test_str = "ADC Data\r\nDoor Data\r\nSensor Data\r\nCurrent Floor\r\nStatus\r\n";
        uart_write_bytes(uart_num, (const char *)test_str, strlen(test_str));
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
#endif

void app_main(void)
{
    #if 0
    // Initialize UART 2 for external serial communication
    uart_setup();
    
    setUpGPIO();

    gpio_queue = xQueueCreate(10, sizeof(uint32_t));
    /* Create task that will be trigger by interrupt */
    xTaskCreate(&task2, "task 2", 2048, NULL, 10, NULL);

    // Initialize UART task which would be Task 5 for debugging all status of sensors, doors, and current stage
    xTaskCreate(&task5, "task5", 2048, NULL, 10, NULL);

    #endif 

    setADC();
    xTaskCreate(&adc_test, "adc test", 2048, NULL, 3, NULL);
}
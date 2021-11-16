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

void uart_task(void *arg)
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

void app_main(void)
{
    // Initialize UART 2 for external serial communication
    uart_setup();
    // Initialize UART task which would be Task 5 for debugging all status of sensors, doors, and current stage
    xTaskCreate(uart_task, "uart_task", 2048, NULL, 10, NULL);
}
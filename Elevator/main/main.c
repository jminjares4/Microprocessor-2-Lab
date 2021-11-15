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
#define UART_0_TX 1
#define UART_0_RX 3

#define UART_BUFFER_SIZE 1024
const uart_port_t uart_num = UART_NUM_0;
void uart_setup(void)
{

    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
    ESP_ERROR_CHECK(uart_set_pin(uart_num, UART_0_TX, UART_0_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    ESP_ERROR_CHECK(uart_driver_install(uart_num, UART_BUFFER_SIZE * 2, UART_BUFFER_SIZE * 2, 0, NULL, 0));
}
#define TAG "RX TAG"
void uart_task(void *arg)
{
    while (1)
    {
        // Write data to UART.
        // char *test_str = "This is a test string.\r\n";
        // uart_write_bytes(uart_num, (const char *)test_str, strlen(test_str));
        // vTaskDelay(1000 / portTICK_RATE_MS);
        // Read data from UART.
        const uart_port_t uart_num = UART_NUM_0;
        uint8_t data[1];
        int length = 0;
        ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t *)&length));
        length = uart_read_bytes(uart_num, data, length, 100);
        data[length] =0;
        uart_write_bytes(uart_num, (const char *)data, 1);
        
        // ESP_LOGI(TAG, "bytes: '%s'", data);
        // ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);
        //  vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void app_main(void)
{
    uart_setup();
    xTaskCreate(uart_task, "uart_task", 2048, NULL, 10, NULL);
}
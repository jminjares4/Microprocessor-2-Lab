/**
 * @file serial_communication.c
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief serial_communication.h source code
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "inc/serial_communication.h"

SerialComm externalSerial = {
    .gpio_rx = UART_2_RX,
    .gpio_tx = UART_2_TX,
    .gpio_rts = NO_PIN,
    .gpio_cts = NO_PIN,
    .uart_num = UART_2,
    .baud_rate = 9600,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = ONE_STOP_BIT,
    .data_bits = EIGHT_BITS,
};


/**
 * @brief serialCommInit will intialize external serial communication
 *
 * @param serial pass a SerialComm by reference
 * @return None
 */
void serialCommInit(SerialComm *serial){
    uart_config_t uart_config = {
        .baud_rate = serial->baud_rate,
        .data_bits = serial->data_bits,
        .parity = serial->parity,
        .stop_bits = serial->stop_bits,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_param_config(serial->uart_num, &uart_config);
    uart_set_pin(serial->uart_num, serial->gpio_tx,serial->gpio_rx, serial->gpio_rts,serial->gpio_cts);
    uart_driver_install(serial->uart_num, UART_BUFFER_SIZE * 2, UART_BUFFER_SIZE *2 ,0,NULL, 0);
}

/**
 * @brief serial_write will write the bytes that will be sent via serial communication
 *
 * @param serial pass a SerialComm by reference
 * @param str string that will be sent via the serial communication
 * @param size length of string
 */
void serial_write(SerialComm * serial, char *str, int size){
    if(size == 0)
        uart_write_bytes(serial->uart_num, (const char *)str, strlen(str));
    else
        uart_write_bytes(serial->uart_num, (const char *)str, size);
}
/**
 * @file serial_communication.h
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief Hardware Application Layer for Serial Communication
 * @version 0.1
 * @date 2021-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef _SERIAL_COMMUNICATION_H_
#define _SERIAL_COMMUNICATION_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

// UART 0 Pins
#define UART_0_RX 3
#define UART_0_TX 1

// UART 1 Pins
#define UART_1_RX 9
#define UART_1_TX 10

// UART 2 Pins
#define UART_2_TX 17
#define UART_2_RX 16

// UART Buffer size
#define UART_BUFFER_SIZE 1024

// UARTs selection
#define UART_0 UART_NUM_0
#define UART_1 UART_NUM_1
#define UART_2 UART_NUM_2

// No pin selection
#define NO_PIN UART_PIN_NO_CHANGE

#define FIVE_BITS UART_DATA_5_BITS
#define SIX_BITS UART_DATA_6_BITS
#define SEVEN_BITS UART_DATA_7_BITS
#define EIGHT_BITS UART_DATA_8_BITS

#define ONE_STOP_BIT UART_STOP_BITS_1
#define ONE_HALF_STOP_BIT UART_STOP_BITS_1_5
#define TWO_STOP_BIT UART_STOP_BITS_2

/**
 * @struct SerialComm serial_communication.h
 * @brief Custom SerialComm structure for UART adaptablity.
 *
 * This structure allows the user to select the UART pins, baud rate, stop bits, parity and data bits
 * ### Example
 * ~~~.c
 * typedef strcut {
 *  int gpio_rx;                 // RX pin
 *  int gpio_tx;                 // TX pin
 *  int gpio_rts;                // RTS pin
 *  int gpio_cts;                // CTS pin
 *  uart_port_t uart_num;        // UART selection
 *  uint32_t baud_rate;          // Baud rate
 *  uart_parity_t parity;        // Parity selection
 *  uart_stop_bits_t stop_bits;  // Stop bits
 *  uart_word_length_T data_bits;// Data bits
 * }SerialComm;
 * ~~~
 */
typedef struct SerialComm
{
    int gpio_rx;                  /*!< gpio rx */
    int gpio_tx;                  /*!< gpio tx */
    int gpio_rts;                 /*!< gpio rts */
    int gpio_cts;                 /*!< gpio cts */
    uart_port_t uart_num;         /*!< uart selection */
    uint32_t baud_rate;           /*!< baud rate */
    uart_parity_t parity;         /*!< parity selection */
    uart_stop_bits_t stop_bits;   /*!< stop bits */
    uart_word_length_t data_bits; /*!< data bits */
} SerialComm;

/**
 * @brief serialCommInit will intialize external serial communication
 *
 * @param serial pass a SerialComm by reference
 * @return None
 */
void serialCommInit(SerialComm *serial);

/**
 * @brief serial_write will write the bytes that will be sent via serial communication
 *
 * @param serial pass a SerialComm by reference
 * @param str string that will be sent via the serial communication
 * @param size length of string
 */
void serial_write(SerialComm *serial, char *str, int size);

#endif
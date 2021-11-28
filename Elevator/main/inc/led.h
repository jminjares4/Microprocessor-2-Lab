/**
 * @file led.h
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief Hardware Application Layer for any LEDs
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _LED_H_
#define _LED_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define HIGH 1 // LOGIC HIGH
#define LOW  0 // LOGIC LOW

#define ONBOARD_LED 2 // Onboard led 

/**
 * @struct Led led.h
 * @brief  This is a custom library for easy use of Led without the struggle of doing  all the hardware intializatio and selection.
 * 
 */

/**
 * @enum state_t led.h 
 * @brief Led struct for any outputs
 * 
 * Enumeration of the led state 
 * 
 * ### Example 
 * ~~~.c
 * typedef enum {
 *  LED_OFF = 0, // OFF
 *  LED_ON = 1, // ON
 * }state_t;
 * ~~~
 **/
typedef enum state_t{
    LED_OFF = 0, /*!< led off */
    LED_ON = 1, /*!< led on */
}state_t;

/**
 * @struct Led led.h 
 * @brief Led struct for any outputs
 * 
 * ### Example 
 * ~~~.c
 * typedef struct{
 *  gpio_num_t gpio; // gpio pin
 *  enum state; //state of the led 
 * }Led;
 * ~~~
 * 
 * @see enum state_t
 */
typedef struct {
    gpio_num_t gpio; /*!< gpio pin */
    state_t state; /*!< led state */
}Led;

/**
 * @brief Led initialization for any led
 * 
 * @param led pass a Led by reference
 * @return None
 */
void ledInit(Led *led);

/**
 * @brief ledOn will set high the instance of the led 
 * 
 * @param led pass a Led by reference
 * @return None
 * @note ledOn will change the state of the led @see state
 */
void ledOn(Led *led);

/**
 * @brief ledOff will set low the instance of the led 
 * 
 * @param led pass a Led by reference
 * @note None
 * @note ledOn will change the state of the led @see state
 */
void ledOff(Led *led);

#endif 
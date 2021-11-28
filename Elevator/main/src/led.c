/**
 * @file led.c
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief led.h source code
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "inc/led.h"

Led onboard = {
    .gpio = ONBOARD_LED,
    .state = LED_OFF,
};

/**
 * @brief Led initialization for any led
 * 
 * @param led pass a Led by reference
 * @return None
 */
void ledInit(Led *led){
    gpio_pad_select_gpio(led->gpio);
    gpio_set_direction(led->gpio, GPIO_MODE_OUTPUT);
    led->state = LED_OFF;
}

/**
 * @brief ledOn will set high the instance of the led 
 * 
 * @param led pass a Led by reference
 * @return None
 * @note ledOn will change the state of the led @see state
 */
void ledOn(Led *led){
    gpio_set_level(led->gpio, HIGH);
    led->state = LED_ON;
}

/**
 * @brief ledOff will set low the instance of the led 
 * 
 * @param led pass a Led by reference
 * @note None
 * @note ledOn will change the state of the led @see state
 */
void ledOff(Led *led){
    gpio_set_level(led->gpio, LOW);
    led->state = LED_OFF;
}
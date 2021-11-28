/**
 * @file motion_sensor.h
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief Hardware Application Layer for the motion sensor
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _MOTION_SENSOR_H_
#define _MOTION_SENSOR_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define ESP_INTR_FLAG_DEFAULT 0 //default interrupt flag

#define MOTION_SENSOR_GPIO 21 //motion sensor gpio 
#define PULL_SEL_EN 1 //Macro for pull selection

/**
 * @struct MotionSensor motion_sensor.h
 * @brief Custom MotionSensor structure to automate setup
 * 
 * This structure allows the user to select its gpio pin, and set for pullup or pulldown base on configurationand lastly if the button will be read as input or interrupt.
 * 
 * ### Example
 * ~~~.c
 * typedef struct{
 *      gpio_num_t gpio; // gpio number
 *      union{
 *          gpio_pullup_t up; //pullup
 *          gpio_pulldown_t down; //pulldown
 *      }pull_sel; //select configuration 
 *      void (*func)(void *arg); //gpio interrupt routine
 * }MotionSensor;
 * ~~~
 */
typedef struct MotionSensor{
    gpio_num_t gpio; /*!< gpio number */
    union {
        gpio_pullup_t up;  /*!< gpio configuration for pullup */
        gpio_pulldown_t down;  /*!< gpio configuration for pulldown */
    }pull_sel;
    void (*func)(void *arg); /*!< gpio interrupt routine */
}MotionSensor;

/**
 * @brief motionSensorInit will intialize motion sensor for interrupt routine
 * 
 * @param sensor pass a MotionSensor by reference
 * @return None
 */
void motionSensorInit(MotionSensor *sensor);

/**
 * @brief motionSensorInterrupt will be an general routine for motionSensor interrupt.
 * 
 * @param arg interrupt argument
 */
extern void motionSensorInterrupt(void *arg);

#endif
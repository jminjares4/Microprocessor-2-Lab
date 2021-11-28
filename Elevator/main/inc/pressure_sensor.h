/**
 * @file pressure_sensor.h
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief Hardware Application Layer for Pressure Sensor 
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _PRESSURE_SENSOR_H_
#define _PRESSURE_SENSOR_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"

#define PRESSURE_SENSOR_ADC_WIDTH (adc_bits_width_t)(ADC_WIDTH_BIT_12) // ADC width of 12 Bits 2**12 - 1
#define PRESUSRE_SENSOR_CH ADC1_CHANNEL_5 // pressure sensor channel
#define PRESSURE_SENSOR_ADC_ATTEN (adc_atten_t)(ADC_ATTEN_DB_11)  // ADC attenuation set at 11 for range of 2600mV
#define PRESSURE_SENSOR_THRESHOLD 1000 //pressure sensor threshold 

/**
 * @struct PressureSensor pressure_sensor.h
 * @brief PressureSensor structure for Force-Sensitive Sensor
 * 
 * This is a custom data structure for Force-Sensitive Sensor
 * 
 * ### Example 
 * ~~~.c
 * typedef struct{
 *      adc_bits_width_t width; //ADC width
 *      adc1_channel_t channel; // sensor channel
 *      adc_atten_t atten; // ADC attenuation
 * }PressureSensor;
 * ~~~
 */
typedef struct {
    adc_bits_width_t width; /*!< ADC width */
    adc1_channel_t channel; /*!< Sensor channel*/
    adc_atten_t atten; /*!< ADC attenuation */
}PressureSensor;

/**
 * @brief PressureSensor initialization for force-sensitive sensor
 * 
 * @param ps pass a PressureSensor by reference 
 */
void pressureSensorInit(PressureSensor *ps);

/**
 * @brief Read channel of the PressureSensor
 * 
 * @param ps pass a PressureSensor by reference
 * @return int adc raw from the sensor
 */
int read_pressure_sensor(PressureSensor *ps);
#endif
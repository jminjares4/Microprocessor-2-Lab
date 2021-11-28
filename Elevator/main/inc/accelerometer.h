/**
 * @file accelerometer.h
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief Hardware Application Layer for ADXL335 Accelerometer
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

#include "driver/adc.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/**
 * @brief Accelerometer Macros for modularity
 * @note  Adjustable Macros to channel any of the adc pins of the accelerometer
 */
#define ACC_ADC_WIDTH (adc_bits_width_t)(ADC_WIDTH_BIT_12) // ADC width of 12 Bits 2**12 - 1
#define X_AXIS (adc1_channel_t)(ADC1_CHANNEL_6) //X-axis adc channel 
#define Y_AXIS (adc1_channel_t)(ADC1_CHANNEL_7) //Y-axis adc channel
#define Z_AXIS (adc1_channel_t)(ADC1_CHANNEL_4) //Z-axis adc channel
#define ACC_ADC_ATTEN (adc_atten_t)(ADC_ATTEN_DB_11) // ADC attenuation set at 11 for range of 2600mV

/**
 * @struct Accelerometer accelerometer.h
 * @brief Accelerometer struct for ADXL335
 * 
 * This is a custom data structure for the ADXL335 accelerometer
 * 
 * ### Example
 * ~~~.c
 * typedef struct{
 *      adc_bits_width_t width; //ADC width
 *      adc1_channel_t xaxis; // X-axis channel
 *      adc1_channel_t yaxis; // Y-axis channel
 *      adc1_channel_t zaxis; // Z-axis channel
 *      adc_atten_t atten; // ADC attenuation
 * }Accelerometer;
 * ~~~
 **/
typedef struct
{
    adc_bits_width_t width;     /*!< ADC width */
    adc1_channel_t xaxis;       /*!< X-axis channel */
    adc1_channel_t yaxis;       /*!< Y-axis channel */
    adc1_channel_t zaxis;       /*!< Z-axis channel */
    adc_atten_t atten;          /*!< ADC attenuation */
} Accelerometer;

/**
 * @brief ADC initialization for the accelerometer
 * 
 * @param acc pass a Accelerometer by reference
 * @return None
 * 
 */
void adcInit(Accelerometer *acc);

/**
 * @brief Read axis for the accelerometer
 * 
 * @param acc pass a Accelerometer by reference
 * @param id  adc channel raw data
 * @return int adc raw from the desire id
 * 
 * @note 0 X_AXIS, 1 Y_AXIS, 2 Z_AXIS, anything else will return 0
 */
int read_axis(Accelerometer *acc, int id);

#endif
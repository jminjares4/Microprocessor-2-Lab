/**
 * @file accelerometer.c
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief accelerometer.h source code
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "inc/accelerometer.h"

/* ADXL335 Predefine structure */
Accelerometer acc = {
    .width = ACC_ADC_WIDTH,
    .xaxis = X_AXIS,
    .yaxis = Y_AXIS,
    .zaxis = Z_AXIS,
    .atten = ACC_ADC_ATTEN,
};

/**
 * @brief ADC initialization for the accelerometer
 * 
 * @param acc pass a Accelerometer by reference
 * @return None
 * 
 */
void adcInit(Accelerometer *acc)
{
    adc1_config_width(acc->width); // set the width for the adc instance 

    //set the attentuation of each axis of the accelerometer
    adc1_config_channel_atten(acc->xaxis, acc->atten);
    adc1_config_channel_atten(acc->yaxis, acc->atten);
    adc1_config_channel_atten(acc->zaxis, acc->atten);
    return;
}

/**
 * @brief Read axis for the accelerometer
 * 
 * @param acc pass a Accelerometer by reference
 * @param id  adc channel raw data
 * @return int adc raw from the desire id
 * 
 * @note 0 X_AXIS, 1 Y_AXIS, 2 Z_AXIS, anything else will return 0
 */
int read_axis(Accelerometer *acc, int id)
{
    // int adcRaw = 0;
    // switch (id)
    // {
    //     case 0:
    //         adcRaw = adc1_get_raw(acc->xaxis);
    //         break;
    //     case 1:
    //         adcRaw = adc1_get_raw(acc->yaxis);
    //         break;
    //     case 2:
    //         adcRaw = adc1_get_raw(acc->zaxis);
    //         break;
    //     default:
    //         adcRaw = 0;
    // }
    // return adcRaw;

    // int adcRaw = 0;
    // if(id == 0){
    //      adcRaw = adc1_get_raw(acc->xaxis);
    // }else if(id == 1){
    //      adcRaw = adc1_get_raw(acc->yaxis);
    // }else if(id == 2){
    //      adcRaw = adc1_get_raw(acc->zaxis);
    // }else{
    //     adcRaw = 0;
    // }
    // return adcRaw;

    /**
     * if 0:
     *      read x-axis
     * elif 1:
     *      read y-axis
     * elif 2:
     *      read z-axis
     * else:
     *      0
     */
    return id == 0 ? adc1_get_raw(acc->xaxis) : id == 1 ? adc1_get_raw(acc->yaxis) : id == 2 ?  adc1_get_raw(acc->zaxis) : 0;
}
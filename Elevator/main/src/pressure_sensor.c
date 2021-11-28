/**
 * @file pressure_sensor.c
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief pressure_sensor.h source code
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "inc/pressure_sensor.h"

PressureSensor pressSens = {
    .width = PRESSURE_SENSOR_ADC_WIDTH,
    .channel = PRESUSRE_SENSOR_CH,
    .atten = PRESSURE_SENSOR_ADC_ATTEN,
};

/**
 * @brief PressureSensor initialization for force-sensitive sensor
 * 
 * @param ps pass a PressureSensor by reference 
 */
void pressureSensorInit(PressureSensor *ps){
    adc1_config_width(ps->width); //set the width of the adc 
    adc1_config_channel_atten(ps->channel, ps->atten); //set channel and attenuation
}

/**
 * @brief Read channel of the PressureSensor
 * 
 * @param ps pass a PressureSensor by reference
 * @return int adc raw from the sensor
 */
int read_pressure_sensor(PressureSensor *ps){
    return adc1_get_raw(ps->channel); //read the channel of the pressure sensor
}
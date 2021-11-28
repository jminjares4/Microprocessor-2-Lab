/**
 * @file servo.h
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief Hardware Application Layer for Servo SG90 motor
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _SERVO_H_
#define _SERVO_H_

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/mcpwm.h"

#define SERVO_PWM_UNIT (mcpwm_unit_t)MCPWM_UNIT_0 // pwm unit 
#define SERVO_PWM_SIGNAL (mcpwm_io_signals_t)(MCPWM0A) // pwm signal
#define SERVO_GPIO 18 // servo gpio pin
#define SERVO_FREQ 50 // default frequency for servo
#define SERVO_TIMER (mcpwm_timer_t)MCPWM_TIMER_0 // default timer

#define SERVO_MIN_PULSEWIDTH_US (1000) // min pulse width
#define SERVO_MAX_PULSEWIDTH_US (2000) // max pulse width
#define SERVO_MAX_DEGREE        (90)   //max degree

/**
 * @struct Servo servo.h
 * @brief Servo struct for SG90 servo motor
 * 
 * This is a custom data structure for the SG90 motor
 * 
 * ### Example 
 * ~~~.c
 * typedef struct {
 *  mcpwm_timer_t timerNum; // timer selection 
 *  mcpwm_unit_t pwmUnit; // pwm unit 
 *  mcpwm_io_signals_t signal; // pwm signal 
 *  gpio_num_t gpio; // pwm gpio pin 
 *  int angle; // servo angle 
 * }Servo;
 * ~~~
 */
typedef struct Servo{
    mcpwm_timer_t timerNum;  /*!< timer selection */
    mcpwm_unit_t pwmUnit;  /*!< pwm unit */
    mcpwm_io_signals_t signal;  /*!< pwm signal */
    gpio_num_t gpio;  /*!< pwm gpio pin */
    int angle;   /*!< servo motor */
}Servo;

/**
 * @brief moveServo will move the servo motor by angles
 * 
 * @param servo pass a Servo by reference
 * @param angle int servo angle movment
 * @note Rangee for -90 to 90 degrees
 */
void moveServo(Servo *servo, int angle);
/**
 * @brief servoInit will initialize servo motor
 * 
 * @param servo pass a Servo motor by reference
 */
void servoInit(Servo *servo);

/**
 * @brief haltServo will stop the timer of the mcpwm
 * 
 * @param servo pass a Servo motor by reference
 * @return None
 */
void haltServo(Servo *servo);

/**
 * @brief startServo will start the time of the mcpwm
 * 
 * @param servo pass a Servo motor by reference
 */
void startServo(Servo *servo);
#endif
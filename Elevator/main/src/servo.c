/**
 * @file servo.c
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief servo.h source code
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "inc/servo.h"

Servo SG90 = {
    .timerNum = SERVO_TIMER,
    .pwmUnit = SERVO_PWM_UNIT,
    .signal = SERVO_PWM_SIGNAL,
    .gpio = SERVO_GPIO,
    .angle = 0
};

static inline uint32_t example_convert_servo_angle_to_duty_us(int angle)
{
    //convert duty cycle to degrees
    return (angle + SERVO_MAX_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (2 * SERVO_MAX_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}

/**
 * @brief moveServo will move the servo motor by angles
 * 
 * @param servo pass a Servo by reference
 * @param angle int servo angle movment
 * @note Rangee for -90 to 90 degrees
 */
void moveServo(Servo *servo, int angle){
    //move servo based on duty cycle
    mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, example_convert_servo_angle_to_duty_us(angle));
    servo->angle = angle; //update servo angle 
}

/**
 * @brief servoInit will initialize servo motor
 * 
 * @param servo pass a Servo motor by reference
 */
void servoInit(Servo *servo){
    //initialize mcpwm
    mcpwm_gpio_init(servo->pwmUnit, servo->signal, servo->gpio);

    //fill pwm config @ 50 hertz on up counter 
    mcpwm_config_t pwm_config = {
        .frequency = SERVO_FREQ,
        .cmpr_a = 0,
        .counter_mode = MCPWM_UP_COUNTER,
        .duty_mode = MCPWM_DUTY_MODE_0,
    };
    // initalize the instance of servo
    mcpwm_init(servo->pwmUnit,servo->timerNum,&pwm_config);
}

/**
 * @brief haltServo will stop the timer of the mcpwm
 * 
 * @param servo pass a Servo motor by reference
 * @return None
 */
void haltServo(Servo *servo){
    mcpwm_stop(servo->pwmUnit,servo->timerNum); // stop mcpwm timer
}

/**
 * @brief startServo will start the time of the mcpwm
 * 
 * @param servo pass a Servo motor by reference
 */
void startServo(Servo *servo){
    mcpwm_start(servo->pwmUnit, servo->timerNum); // start mcpwm timer
}
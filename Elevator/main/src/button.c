/**
 * @file button.c
 * @author Jesus Minjares (https://github.com/jminjares4)
 * @brief button.h source code
 * @version 0.1
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "inc/button.h"

/**
 * @brief Button Initialization for buttons
 * @param button pass a Button by reference
 * @return None
 * @note    buttonInit() is use when the button or input will be read as high or low level
 *          for interrupt intitialization @see buttonInitIRQ()
 */
void buttonInit(Button *button)
{
    if (button->func == NULL) //check if button has a routine
    {
        gpio_pad_select_gpio(button->gpio); //enable pin
        gpio_set_direction(button->gpio, GPIO_MODE_INPUT); //set pin as input
        if (button->pull_sel.up) //check if pull-up is selected
        {
            gpio_set_pull_mode(button->gpio, GPIO_PULLUP_ONLY); //enable pull-up
        }
        else //pull-down selected
        {
            gpio_set_pull_mode(button->gpio, GPIO_PULLDOWN_ONLY); //enable pull-down
        }
    }else{ //warning
        printf("Changed button->func to NULL\n"); 
        button->func = NULL; //set button to a default routine as NULL
    }
}

/**
 * @brief buttonRead will read the gpio pin
 * 
 * @param button pass a Button by reference
 * @return int  return either high or low || 0 or 1
 */
int buttonRead(Button *button)
{
    return gpio_get_level(button->gpio); //get the level of the gpio pin
}

/**
 * @brief buttonInitIRQ will intialize button for interrupt routine
 * 
 * @param button pass a Button by referene
 * @return None
 */
void buttonInitIRQ(Button *button)
{
    gpio_config_t io_conf; // gpio_config_t to store configuration
    if (button->pull_sel.up)//check if pull-up is selected
    {
        io_conf.intr_type = GPIO_INTR_NEGEDGE; // set as NEGEDGE for interrupt
        io_conf.pull_down_en = 0;              // disable pull-down
        io_conf.pull_up_en = 1;                // enable pull-up
    }
    else  //pulldown selected
    {
        io_conf.intr_type = GPIO_INTR_POSEDGE; // set as NEGEDGE for interrupt
        io_conf.pull_down_en = 1; // enable pull-down
        io_conf.pull_up_en = 0;   // disable pull-up
    }
    io_conf.mode = GPIO_MODE_INPUT;                // set input
    io_conf.pin_bit_mask = (1ULL << button->gpio); // set gpio that will be used for input

    gpio_config(&io_conf); //set configuration
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT); //set default flag for interrupts
    gpio_isr_handler_add(button->gpio, button->func, (void *)button->gpio); //pass the gpio number, routine and argument for the routine
}

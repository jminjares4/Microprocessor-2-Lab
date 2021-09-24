/*
    Author:     Jesus Minjares
                Master of Science in Computer Engineering
    Course:     EE 5190 Laboratory for Microprocessors Systems II

    Lab 1B:     The purpose of Lab 1B is to get familiar with Queues in
                FreeRTOS. The lab consist of sending data from an sender task
                into a reciever task. The receiver will wait for the sender to
                feed data into the queue. Once the data is receive
                it will display it in the terminal. 
                
    Date:       09-22-2021
    Pinout:
                                         +-----------------------+
                                         | O      | USB |      O |
                                         |        -------        |
                                     3V3 | [ ]               [ ] | VIN
                                     GND | [ ]               [ ] | GND
     Touch3 / HSPI_CS0 / ADC2_3 / GPIO15 | [ ]               [ ] | GPIO13 / ADC2_4 / HSPI_ID / Touch4
 CS / Touch2 / HSPI_WP / ADC2_2 /  GPIO2 | [ ]               [ ] | GPIO12 / ADC2_5 / HSPI_Q / Touch5
      Touch0 / HSPI_HD / ADC2_0 /  GPIO4 | [ ]               [ ] | GPIO14 / ADC2_6 / HSPI_CLK / Touch6
                         U2_RXD / GPIO16 | [ ]               [ ] | GPIO27 / ADC2_7 / Touch7
                         U2_TXD / GPIO17 | [ ]               [ ] | GPIO26 / ADC2_9 / DAC2
                      V_SPI_CS0 /  GPIO5 | [ ]  ___________  [ ] | GPIO25 / ADC2_8 / DAC1
                SCK / V_SPI_CLK / GPIO18 | [ ] |           | [ ] | GPIO33 / ADC1_5 / Touch8 / XTAL32
        U0_CTS / MSIO / V_SPI_Q / GPIO19 | [ ] |           | [ ] | GPIO32 / ADC1_4 / Touch9 / XTAL32
                 SDA / V_SPI_HD / GPIO21 | [ ] |           | [ ] | GPIO35 / ADC1_7 
                  CLK2 / U0_RXD /  GPIO3 | [ ] |           | [ ] | GPIO34 / ADC1_6 
                  CLK3 / U0_TXD /  GPIO1 | [ ] |           | [ ] | GPIO39 / ADC1_3 / SensVN 
        SCL / U0_RTS / V_SPI_WP / GPIO22 | [ ] |           | [ ] | GPIO36 / ADC1_0 / SensVP 
                MOSI / V_SPI_WP / GPIO23 | [ ] |___________| [ ] | EN 
                                         |                       |
                                         |  |  |  ____  ____  |  |
                                         |  |  |  |  |  |  |  |  |
                                         |  |__|__|  |__|  |__|  |
                                         | O                   O |
                                         +-----------------------+
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

/* Global Queue handle */
QueueHandle_t xQueue;

/*Directive to change from int32_t -> char * -> Data_t */

// #define _BONUS_ TRUE
#define _LAB_ TRUE

/* Basic data structure that will be sent in the Queue*/
typedef struct Data_t{
    char str[10];
    int32_t val;
}Data_t;

/* Sender task will send data into the queue */
static void vSenderTask(void *pvParameters){
    /*Check for directive */
    #ifdef _BONUS_
        Data_t *IValueToSend = (Data_t*)pvParameters; //store argument
    #elif defined(_LAB_)
        char *IValueToSend = (char *)pvParameters; //store argument
    #else
        int32_t IValueToSend = (int32_t) pvParameters; //store argument
    #endif
    
    BaseType_t xStatus; //hold status 

    for(;;){
         /*Check for directive */
        #ifdef _BONUS_
            xStatus = xQueueSendToBack(xQueue, IValueToSend, 0);  //send data into queue
        #elif defined(_LAB_)
            xStatus = xQueueSendToBack(xQueue, &IValueToSend, 0); //send data into queue
        #else
            xStatus = xQueueSendToBack(xQueue, &IValueToSend, 0); //send data into queue
        #endif
        if(xStatus != pdPASS){
            printf("Could not send to the queue.\n");  
        }
    }
}
static void vRecieverTask(void *pvParameters){
    /*Check for directive */
    #ifdef _BONUS_
        Data_t IRecievedValue;
    #elif defined(_LAB_)
        char *IRecievedValue;
    #else
        int32_t IRecievedValue;
    #endif
    
    BaseType_t xStatus; //hold status 

    /* Variable that hold the number of tick that the Queue will wait*/
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

    for(;;){
        if(uxQueueMessagesWaiting(xQueue) != 0){
            printf("Queue should have been empty!\n");
        }
        xStatus = xQueueReceive(xQueue, &IRecievedValue, xTicksToWait); //recieve data from queue
        /* Check if data was received from the queue */
        if(xStatus == pdPASS){
            #ifdef _BONUS_
                printf("Recieved= %s,%d\n", IRecievedValue.str, IRecievedValue.val);
            #elif defined(_LAB_)
                printf("Recieved= %s\n", IRecievedValue);
            #else
                printf("Received =%d\n", IRecievedValue);
            #endif
        }else{
            printf("Could not recieve from the queue.\n");
        }
    }
}
void app_main(void){
    /*Check for directive */
    /*  Create static variable so they will be store in static memory
        and once the main terminate, it content will not be corrupted.
    */
    #ifdef _BONUS_
        /* Create Queue of type Data_t */
        static Data_t data1 = {"EE4178", 10};
        static Data_t data2 = {"Fall2021", 20};
        xQueue = xQueueCreate(5, sizeof(Data_t));
    #elif defined(_LAB_)
        static const char *data1 = "EE4178";
        static const char *data2 = "Fall2021";
        xQueue = xQueueCreate(5, sizeof(char*));
    #else
        /* Create Queue of type int32_t */
        static int32_t data1 = 10, data2 = 20;
        xQueue = xQueueCreate(5, sizeof(int32_t));
    #endif
    /* Check if the queue was create successfully */
    if(xQueue != NULL){
        /*Check for directive */
        #ifdef _BONUS_
            /* Create sender tasks and send Data_t as arguments */
            xTaskCreate(vSenderTask, "Sender1", 2048, (void *)&data1, 1, NULL);
            xTaskCreate(vSenderTask, "Sender2", 2048, (void *)&data2, 1, NULL);
        #elif defined(_LAB_)
            xTaskCreate(vSenderTask, "Sender1", 2048, (void *)data1, 1, NULL);
            xTaskCreate(vSenderTask, "Sender2", 2048, (void *)data2, 1, NULL);
        #else
            /* Create sender tasks and send int32_t as arguments */
            xTaskCreate(vSenderTask, "Sender1", 2048, (void *)data1, 1, NULL);
            xTaskCreate(vSenderTask, "Sender2", 2048, (void *)data2, 1, NULL);
        #endif 
        /* Create reciever task */
        xTaskCreate(vRecieverTask,"Reciever", 2048, NULL, 2, NULL);
        /*Disable vTaskStartScheduler as ESP32 automatically run once main terminates */
    //    vTaskStartScheduler();
    }
}

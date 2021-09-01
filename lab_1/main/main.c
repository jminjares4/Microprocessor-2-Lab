/*
    Author: Jesus Minjares
            Master of Science in Computer Engineering
    Date:   09-01-2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "esp_log.h"

//Macro for the tag of the esp logging
#define TAG "TASK_LOG"

//Data structure to send to the task as arguements
typedef struct {
    int number;
    int delayMs;
    char str[25];
}Data_t;

//Generic Task that will use Data_t as an arguement
void vTask(void *pvParameters){
    Data_t *data = (Data_t*)(pvParameters);
    while(1){
        #ifdef __ESP_LOG_H__
            ESP_LOGI(TAG, "String: %s\t Number: %i\n", data->str, (int)data->number);
        #else
            printf("String: %s\t Number: %i\n", data->str, (int)data->number);
        #endif
        vTaskDelay(data->delayMs/ portTICK_RATE_MS);
    }
}
//Main
void app_main(void){
    /*Create static variables to pass by reference to the task*/
    static Data_t data1 = {.number = 1, .delayMs = 1000};
    strcpy(data1.str, "Hello world!!");

    static Data_t data2 = {.number = 2, .delayMs = 1000};
    strcpy(data2.str, "Hello world!!");

    static Data_t data3 = {.number = 3, .delayMs = 1000};
    strcpy(data3.str, "Hello world!!");

    /*Handle will be associate to task*/
    TaskHandle_t task1 = NULL, task2 = NULL, task3 = NULL; 

    /*Create three task with the Data_t as a parameter*/
    xTaskCreate(vTask, "Task 1", 2048, (void * const)&data1, 3,&task1);
    xTaskCreate(vTask, "Task 2", 2048, (void * const)&data2, 3, &task2);
    xTaskCreate(vTask, "Task 3", 2048, (void * const)&data3, 3, &task3);
}


#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t xSemaphore = NULL;
void task1(void *pvParameter)
{
    while(1) {
        if(xSemaphore != NULL){
            if(xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE){
                printf("Task 1\n");
                vTaskDelay(2000/portTICK_RATE_MS);
                xSemaphoreGive( xSemaphore );
            }
            else{
                printf("Waiting for semaphore...\n");
                vTaskDelay(100 / portTICK_RATE_MS);
            }
        }
    }
}
void task2(void *pvParameter)
{
    while(1) {
        if(xSemaphoreTake(xSemaphore,portMAX_DELAY) == pdTRUE){
            printf("Task 1\n");
            vTaskDelay(2000/portTICK_RATE_MS);
            xSemaphoreGive( xSemaphore );
        }
        else{
            printf("Waiting for semaphore...\n");
            vTaskDelay(100 / portTICK_RATE_MS);
        }
    }
}
void app_main()
{
 xSemaphore = xSemaphoreCreateBinary();
 if( xSemaphore != NULL )
 {
    xTaskCreate(&task1,"task1",2048,NULL,5,NULL);
    xTaskCreate(&task2,"task2",2048,NULL,5,NULL);
     // The semaphore was created successfully.
     // The semaphore can now be used.
 }

//  xTaskCreate(&task3,"task3",4096,NULL,6,NULL);
//  xTaskCreate(&task4,"task4",4096,NULL,7,NULL);
}
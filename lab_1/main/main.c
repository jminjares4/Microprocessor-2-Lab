#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

static void vTask(void *pvParameters){
    int *number = (pvParameters);
    int num = *number;
    while(1){
        printf("Hello from thread: %d\n", num);
        vTaskDelay(2000 / portTICK_RATE_MS);
    }
}

void app_main(void){
    const int *num1 = (int*)1;
    const int *num2 = (int*)2;
    const int *num3 = (int*)3;
    xTaskCreate(vTask, "Task 1", 2048, (void * const)&num1, 5, NULL);
    xTaskCreate(vTask, "Task 2", 2048, (void * const)&num2, 5, NULL);
    xTaskCreate(vTask, "Task 3", 2048, (void * const)&num3, 5, NULL);
}
#if 0
static void vTask_1(void *pvParameters){
    while(1){
        printf("Task 1\n");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
static void vTask_2(void *pvParameters){
    while(1){
        printf("Task 2\n");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
static void vTask_3(void *pvParameters){
    while(1){
        printf("Task 3\n");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
void app_main(){
    xTaskCreate(vTask_1, "Task 1", 1024, NULL, 4, NULL);
    xTaskCreate(vTask_2, "Task 2", 1024, NULL, 4, NULL);    
    xTaskCreate(vTask_3, "Task 3", 1024, NULL, 4, NULL);    
}
#endif

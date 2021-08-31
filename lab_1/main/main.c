#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

// static void vTaskJesus(void *pvParameters){
//     int *number = (pvParameters);
//     while(1){
//         printf("Hello from thread: %d\n", *number);
//         vTaskDelay(1000 / portTICK_RATE_MS);
//        // free(number);
//     }
// }

// void app_main(void){
//     const int *num1 = (int*)1;
//     const int *num2 = (int*)2;
//     const int *num3 = (int*)3;
//     xTaskCreate(vTaskJesus, "Task 1", 512, (void * const)&num1, 2, NULL);
//     xTaskCreate(vTaskJesus, "Task 2", 512, (void * const)&num2, 3, NULL);
//     xTaskCreate(vTaskJesus, "Task 3", 512, (void * const)&num3, 4, NULL);
// }

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

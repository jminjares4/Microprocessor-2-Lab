# Lab 1
## **FREERTOS, TASK AND SEMAPHORES**
### **Goals**
***
* Given the program template shown in listing 1, edit it so that using free RTOS, you create four different tasks.
* Make task one run every two seconds. Task two should run twice as fast as task one. Task three should run every time either task one or task two run. And task four should run every time Task 3 runs.
* Print “Task X running”for every task in the console.

### **Bonus**
***
* Modify the code so that you only use the delay function in one of the tasks.+10

### **Template Code**
~~~c
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
SemaphoreHandle_t xSemaphore = NULL;
void task1(void *pvParameter)
{
    while (1)
    {
        printf("Task 1\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
void app_main()
{
    xSemaphore = xSemaphoreCreateBinary();
    xTaskCreate(&task1, "task1", 4096, NULL, 5, NULL);
    xTaskCreate(&task2, "task2", 4096, NULL, 5, NULL);
    xTaskCreate(&task3, "task3", 4096, NULL, 6, NULL);
    xTaskCreate(&task4, "task4", 4096, NULL, 7, NULL);
}

~~~

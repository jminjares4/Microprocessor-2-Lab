# Lab 1B
## **FreeRTOS: Queue**
### **Goals**
***
* Given the program template in Listing 1, create a program which will create a queue to send and receive data.
* Send data to the queue from multiple tasks,sending integers10 and 20.
* Receive and print data from the queue
* The Listing 1 is a demonstration for integer, show a queue for strings “EE4178” and “Fall2021”.

### **Bonus**
***
* Modify the code by sending structures on a queue. +10

### **Template Code**

~~~c
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
QueueHandle_t xQueue;
int main(void)
{
    xQueue = xQueueCreate(5, sizeof(int32_t));
    if (xQueue != NULL)
    {
        xTaskCreate(vSenderTask, "Sender1", 1000, (void *)10, 1, NULL);
        // Sender2 here.
        xTaskCreate(vReceiverTask, "Receiver", 1000, NULL, 2, NULL);
        vTaskStartScheduler();
    }
    else
    {
    }
}
static void vSenderTask(void *pvParameters)
{
    int32_t lValueToSend;
    BaseType_t xStatus;
    lValueToSend = (int32_t)pvParameters;
    for (;;)
    {
        xStatus = xQueueSendToBack(xQueue, &lValueToSend, 0);
        if (xStatus != pdPASS)
        {
            vPrintString("Could not send to the queue.\r\n");
        }
    }
}
static void vReceiverTask(void *pvParameters)
{
    int32_t lReceivedValue;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
    for (;;)
    {
        if (uxQueueMessagesWaiting(xQueue) != 0)
        {
            vPrintString("Queue should have been empty!\r\n");
        }
        xStatus = xQueueReceive(xQueue, &lReceivedValue, xTicksToWait);
        if (xStatus == pdPASS)
        {
            vPrintStringAndNumber("Received = ", lReceivedValue);
        }
        else
        {
            vPrintString("Could not receive from the queue.\r\n");
        }
    }
}
~~~

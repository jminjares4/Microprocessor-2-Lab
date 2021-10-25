/*
Author: Jesus Minjares
        Master of Science in Computer Engineering
Date:   10-25-2021

Goal:   Generate a deadlock using binary semaphores.
        Task 1 will wait for Task 3 and then intiate Task 2.
        Task 2 will wait for Task 1 and then intiate Task 3.
        Task 3 will wait for Task 2 and then intiate Task 1.


          Task 1
      |            \
    Task 3   <-   Task 2   


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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

/* Create global semaphores flags */
SemaphoreHandle_t  sem1 = NULL, sem2 = NULL, sem3 = NULL;

#define DEADLOCK_OFF 

void Task1(void *pvParameter){
    printf("Easy version\n");
    while(1){
        /* Wait for Task 3 flag */
        xSemaphoreTake(sem3, portMAX_DELAY);
        /* Display message */
        printf("Task 1 running\n");
        vTaskDelay(100/portTICK_RATE_MS);
        /* Send semaphore 1*/
        xSemaphoreGive(sem1);
    }
}
/* Task 2 */
void Task2(void *pvParameter){
    while(1){     
        /* Wait for Task 1 flag */
        xSemaphoreTake(sem1, portMAX_DELAY);
        /*Display message */
        printf("Task 2 running\n");
        vTaskDelay(100/portTICK_RATE_MS);
        /* Send semaphore 2 */
        xSemaphoreGive(sem2);
    }
}
/* Task 3 */
void Task3(void *pvParameters){
    while(1){
        /* Wait for Task 2 flag */
        xSemaphoreTake(sem2, portMAX_DELAY);
        /* Display message */
        printf("Task 3 running\n");
        vTaskDelay(100/portTICK_RATE_MS);
        /* Send semaphore 3 */
        xSemaphoreGive(sem3);
    }
}
void app_main(void){

    sem1 = xSemaphoreCreateBinary(), sem2 = xSemaphoreCreateBinary(), sem3 = xSemaphoreCreateBinary();

    xTaskCreate(&Task1, "Task 1", 2048, NULL, 4, NULL);
    xTaskCreate(&Task2, "Task 2", 2048, NULL, 4, NULL);
    xTaskCreate(&Task3, "Task 3", 2048, NULL, 4, NULL);
    /* The following code will generate a deadlock as all task are consistenly
       waiting for another task resource to intiate it task. In order remove deadlock
       set one of the binary flags as 1
    */
    /* Binary flags */
    #ifdef DEADLOCK_OFF
    xSemaphoreGive(sem1); //set semaphore 3 Output: 3,2,1
    // xSemaphoreGive(sem2); //set semaphore 3 Output: 2,3,1
    // xSemaphoreGive(sem3); //set semaphore 3 Output: 1,2,3
    #endif 
}

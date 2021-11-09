/*
Author: Jesus Minjares
        Master of Science in Computer Engineering
Date:   11-01-2021

Goal:   Generate a priority inheritance to avoid priority inversion problem.
        T1 < T2 < T3
        Task 1 will have the lowest priority.
        Task 2 will have the middle priority.
        Task 3 will have the highest priority.

        Task 1 and Task 3 will share a resource, therefore will have 
        conflict for their critical section.
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
#include <stdbool.h>

/* Global semaphore */
SemaphoreHandle_t sem = NULL;
/* Preprocessor for different scenarios */
#define PRIORITY_INVERSION false
#define PRIORITY_INHERITANCE true

/* Task 1 */
void task1(void *param){
    while (1){
        /* wait() */
        xSemaphoreTake(sem, portMAX_DELAY);
        /* critical section */
        printf("Task 1 running!!!\n");
        vTaskDelay(5000 / portTICK_RATE_MS);
        /* signal() */
        xSemaphoreGive(sem);
    }
}
/* Task 2 */
void task2(void *param){
    while (1){
        printf("Running Task 2\n");
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
/* Task 3 */
void task3(void *param){
    while (1){
        /* wait() */
        xSemaphoreTake(sem, portMAX_DELAY);
        /* critical section */
        printf("Task 3 running!!!\n");
        /* signal() */
        xSemaphoreGive(sem);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void app_main(void)
{
    #ifdef PRIORITY_INVERSION
        #if PRIORITY_INVERSION == true
            /*
                Create priority inversion by using binary semaphores.
                With the use of binary semaphore it will allow task to
                wait all locks to be release no matter the priority. Therefore,
                by limiting the task to release the semaphore until its done it will
                create a priority inversion scenario that could be fatal for the system.
            */
            sem = xSemaphoreCreateBinary(); //create binary semaphore
            xSemaphoreGive(sem); //increment semaphore, to avoid deadlock
        #endif
    #endif
    #ifdef PRIORITY_INHERITANCE
        #if PRIORITY_INHERITANCE == true
            /*  
                In order to avoid the priority inversion
                problem, we must change the binary semaphore to
                mutex. FreeRTOS mutex has predefine inheritance which
                states that when a Task x is running at a critical
                section but Task y with a higher priority and same
                critical section will take over.
            */
            sem = xSemaphoreCreateMutex();
        #endif
    #endif
    /*
        Low -> High priority
        Task 1 < Task 2 < Task 3
        t1 < t2 < t2
    */
    xTaskCreate(&task1, "Task 1", 2048, NULL, 4, NULL); //low
    xTaskCreate(&task2, "Task 2", 2048, NULL, 5, NULL); //mid
    xTaskCreate(&task3, "Task 3", 2048, NULL, 6, NULL); //high
}

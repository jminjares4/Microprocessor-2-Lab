# Lab 04
## **DAC Peripheral**
### **Goals**
*** 
* Using the DAC peripheral create a task to output a triangular wave on GPIO 25.
* Using the DAC peripheral create a task to output a sine wave in GPIO 26
* Use the code in listing 1 to start your project 

### **Bonus**
***
* Make the sine wave have a 10 hz frequency. + 10

### **Template Code**
~~~c
#include <stdio.h>
#include <math.h>
#include "sdkconfig.h"
#include <driver/dac.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
void createTriangleWave(void *pvParameter)
{
    dac_output_enable(DAC_CHANNEL_1);
    static int i = 0;
    while (1)
    {
        dac_output_voltage(DAC_CHANNEL_1, i);
        // compute trialgular waveform value
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
void createSineWave(void *pvParameter)
{
    dac_output_enable(DAC_CHANNEL_2);
    static int i = 0;
    float val;
    int n;
    while (1)
    {
        // compute sine waveform value
        dac_output_voltage(DAC_CHANNEL_2, n);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
void app_main()
{
    xTaskCreate(&createTriangleWave, "createTriangleWave", 4096, NULL, 5, NULL);
    xTaskCreate(&createSineWave, "createSineWave", 4096, NULL, 5, NULL);
}
~~~

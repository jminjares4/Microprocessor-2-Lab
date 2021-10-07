# Lab 03
## **Peripherals and Queues:ADC and PWM (LEDC)**
### **Goals**
*** 
* With the help of the ADC and the LEDC API’s, initialize the peripherals and create a task to perform the readings of the ADC every 100 millisecond.
* This task should feed the information into a queue.
* Create a task that synchronous to the queue to update the PWM’s duty cycle based on the value read by the ADC.
* Modify the program in listing 1 to achieve these goals.

### **Bonus**
***
* Add a port interrupt to stop and start the PWM signal.+10

### **Modify the following code**
***
<img width="428" alt="lab3 " src="https://user-images.githubusercontent.com/60948298/136305157-b2b8c718-20e2-4f60-a98a-3fe085de3306.png">

<img width="380" alt="lab3_1" src="https://user-images.githubusercontent.com/60948298/136305166-88af8401-2f00-4d32-9945-55127a2487c4.png">

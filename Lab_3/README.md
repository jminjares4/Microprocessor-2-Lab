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
<img width="407" alt="lab_2_image_0" src="https://user-images.githubusercontent.com/60948298/134283707-57f65366-fad6-4c31-9dc2-ff7327c1cb5e.png">
<img width="409" alt="lab_2_image_1" src="https://user-images.githubusercontent.com/60948298/134283712-27e15f32-9094-4591-bb5e-5cfc64c14fe2.png">

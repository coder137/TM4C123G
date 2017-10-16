#include <stdint.h>

#include "TM4C123.h"                    // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

//created libraries
#include "serial.h"
#include "utility.h"

void blink_init(void);
void blink(void);

void vBlinkTask(void *pvParameters);
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);


int main(void)
{
    serial_init();
    
    //Blink Task runs here
    xTaskCreate(vBlinkTask, "BlinkTask", 1000, NULL, 1, NULL);
    
    //Task 1 Created which creates task 2
    xTaskCreate(vTask1, "Task1", 1000, "Task1\n", 1, NULL);
    
    vTaskStartScheduler();
    while(1); //should never reach here
}

TaskHandle_t xTask2Handle = NULL;

void vTask1(void *pvParameters)
{
    char *pcData;
    pcData = (char *) pvParameters;
    
    while(1)
    {
        writeString(pcData);
        
        //Creates Task 2 here
        xTaskCreate(vTask2, "Task2", 1000, "Task2\n", 2, &xTask2Handle);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void vTask2(void *pvParameters)
{
    char *pcData;
    pcData = (char *) pvParameters;
    
    
    writeString(pcData);
    writeString("Deleting Task2\n\n");
    
    //Gets Deleted here, we can also call NULL here
    //Used to make things very clear
    vTaskDelete(xTask2Handle);
}


void vBlinkTask(void *pvParameters)
{
    blink();
}

void blink_init(void)
{
    //This is just initialization
    SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR = 0x0e;
	GPIOF->DEN = 0x0e;

	GPIOF->DATA = 0x02;
    //delay(3000);
    vTaskDelay(pdMS_TO_TICKS(3000));
    //GPIOF->DATA = 0x02;
}

void blink(void)
{
    blink_init();
    //infinite loop
    while(1)
    {
        GPIOF->DATA = 0x04;
        //delay(1000);
        vTaskDelay(pdMS_TO_TICKS(1000));
        GPIOF->DATA = 0x08;
        //delay(1000);
        vTaskDelay(pdMS_TO_TICKS(1000));
        
    }
}

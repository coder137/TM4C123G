#include <stdint.h>
#include <stdio.h>

#include "TM4C123GH6PM.h"
#include "FreeRTOS.h"
#include "task.h"


#include "serial.h"

void vTask1(void *pvParameters);
void vTaskPrint(void *pvParameters);
void vPeriodPrint(void *pvParameters);

void blink(void);

int main(void)
{
    //Else you need to add this to every print function. Better to define this globally
    serial_init();
    
    xTaskCreate(vTask1, "BlinkTask", 1000, NULL, 1, NULL);
    
    xTaskCreate(vTaskPrint, "SerialTask", 1000, "Hello\n", 1, NULL);
    xTaskCreate(vTaskPrint, "SerialTask2", 1000, "World\n", 1, NULL);
    
    xTaskCreate(vPeriodPrint, "SerialTask", 1000, "New 2\n", 2, NULL);
    vTaskStartScheduler();
    while(1);
}

void vTask1(void *pvParameters)
{
    blink();
}

void blink(void)
{
    //This is just initialization
    SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR = 0x0e;
	GPIOF->DEN = 0x0e;
	
	GPIOF->DATA = 0x02;
    delay(3000);
    
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

void vTaskPrint(void *pvParameters)
{
    //init it out incase i forget to add it to all other function
    //serial_init();
    char *pcData;
    pcData = (char *) pvParameters;
    while(1)
    {
        //writeChar('L');
        writeString(pcData);
        //delay(1000);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

//Doesnt work for some reasons
void vPeriodPrint(void *pvParameters)
{
    char *pcData;
    pcData = (char *)pvParameters;
    
    //convert and print it to the screen
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
    /* TODO, Write a conversion library
    char str[12];
    sprintf(str, "%d", xLastWakeTime);
    writeString(str);
    */
    while(1)
    {
        //writeString("Task 2");
        writeString(pcData);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));
    }
}

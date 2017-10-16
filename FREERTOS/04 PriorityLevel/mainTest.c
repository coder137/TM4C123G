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

//Task Handle
TaskHandle_t xTask2Handle;

int main(void)
{
    serial_init();
    //Blink Task runs here, for debugging
    xTaskCreate(vBlinkTask, "BlinkTask", 1000, NULL, 1, NULL);
    
    //Add everything here
    xTaskCreate(vTask1, "TaskPrio1", 1000, "Task1\n", 2, NULL);
    xTaskCreate(vTask2, "TaskPrio2", 1000, "Task2\n", 1, &xTask2Handle);
    
    //Start the task Scheduler
    vTaskStartScheduler();
    while(1); //should never reach here
}

void vTask1(void *pvParameters)
{
    UBaseType_t uxPriority;
    
    //Null means that we are getting the priority of this function
    uxPriority = uxTaskPriorityGet(NULL);
    
    char *pcData;
    pcData = (char *)pvParameters;
    
    while(1)
    {
        writeString(pcData);
        //Change priority
        vTaskPrioritySet(xTask2Handle, (uxPriority +1));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


void vTask2(void *pvParameters)
{
    UBaseType_t uxPriority;
    
    uxPriority = uxTaskPriorityGet(NULL);
    
    char *pcData;
    pcData = (char *)pvParameters;
    
    //char *prio;
    while(1)
    {
        writeString(pcData);
        
        writeString("Lowering Priority 3 to 1\n\n");
        vTaskPrioritySet(NULL, (uxPriority - 2));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
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

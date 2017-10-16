#include <stdint.h>

#include "TM4C123.h"                    // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

//created libraries

void blink_init(void);
void blink(void);

void vBlinkTask(void *pvParameters);


int main(void)
{
    //Blink Task runs here
    xTaskCreate(vBlinkTask, "BlinkTask", 1000, NULL, 1, NULL);

    vTaskStartScheduler();
    while(1); //should never reach here
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

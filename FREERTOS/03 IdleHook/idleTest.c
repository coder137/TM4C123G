#include <stdint.h>

#include "TM4C123GH6PM.h"
#include "FreeRTOS.h"
#include "task.h"

#include "serial.h"
#include "blink.h"
#include "utility.h"

void vBlink(void *pvParameters);
void vPrintFunction(void *pvParameters);

static uint32_t ulIdleCycleCount = 0;

int main(void)
{
    //init here
    serial_init();
    
    
    //xTaskCreate(vBlink, "Blink", 1000, NULL, 1, NULL);
    
    // We can print Number from here
    xTaskCreate(vPrintFunction, "PrintNum", 1000, "Hello:\t", 1, NULL);
    //xTaskCreate(vPrintFunction, "PrintNum", 1000, "Num:\t", 1, NULL);
    
    vTaskStartScheduler();
    while(1);
}

void vBlink(void *pvParameters)
{
    blink_init();
    
    while(1)
    {
        blink();
    }
}

//Generic Print Task
void vPrintFunction(void *pvParameters)
{
    char *pcData;
    pcData = (char *)pvParameters;
    char *numData;
    while(1)
    {
        //We get numData from here
        numData = intToString(ulIdleCycleCount);
        
        //print it to the String
        writeString(pcData);
        writeString(numData);
        writeChar('\n');
        vTaskDelay(pdMS_TO_TICKS(1000));
    } 
    
    
}

//When the program is idle do this
void vApplicationIdleHook(void)
{
    //writeChar('W');
    ulIdleCycleCount++;
    /*
    char *d;
    d = intToString(ulIdleCycleCount);
    writeString(d);
    writeChar('\n');
    */
    //Do other small things here, do not add any delay loop at all
}

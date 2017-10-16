#include <stdint.h>

#include "TM4C123.h"                    // Device header

#include "blink.h"
#include "utility.h"

void blink_init(void)
{
    //This is just initialization
    SYSCTL->RCGCGPIO |= 0x20;
	GPIOF->DIR = 0x0e;
	GPIOF->DEN = 0x0e;

	GPIOF->DATA = 0x02;
    delay(3000);
    //GPIOF->DATA = 0x02;
}

void blink(void)
{
    //infinite loop
    GPIOF->DATA = 0x04;
    delay(1000);
    GPIOF->DATA = 0x08;
    delay(1000);
}

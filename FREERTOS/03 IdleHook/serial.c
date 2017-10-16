#include <string.h>

#include "TM4C123GH6PM.h"
#include "serial.h"


void serial_init()
{
    SYSCTL->RCGCUART |= 0x01;
	SYSCTL->RCGCGPIO |= 0x01;

	/*UART0 TX0 AND RX0 use PA0 and PA1*/
	GPIOA->AFSEL |= 0x03;
	GPIOA->PCTL |= 0x11;
	GPIOA->DEN |= 0x03;

	//uart init
	UART0->CTL &= ~(0x01); //disable it for a while
	UART0->IBRD = 104;
	UART0->FBRD = 11;

	UART0->LCRH = 0x60;

	//0x05 is PIOSC, 0x01 is System clock 50MHZ (use SystemCoreClock function)
	UART0->CC = 0x05; //CHECK WHY??? for usb operations sysClk is set to 20MHZ sometimes
	UART0->CTL |= 0x301;
}

void writeChar(char c)
{
    while((UART0->FR & (1 << 5)) != 0);
	UART0->DR = c;
}

void writeString(char *str)
{
    int i;
    for(i=0;i<strlen(str);i++)
    {
        writeChar(str[i]);
    }
}

char readChar(void)
{
    char c;
	//wait till RXFE is 0
	while((UART0->FR & (1<< 4)) != 0);
	c = UART0->DR;
	return c;
}

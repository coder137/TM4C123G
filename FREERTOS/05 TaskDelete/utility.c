#include <stdio.h>

#include "utility.h"

char *intToString(int num)
{
    static char str[12];
    sprintf(str, "%d", num);
    return str;
}

void delay(int ms)
{
    int i, j;
	for(i=0;i<ms;i++)
		for(j=0;j<3180;j++);
}

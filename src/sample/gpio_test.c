#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pcduino_gpio.h"
int main(int argc,char **argv)
{
	int pin;
	if(argc != 3)
	{
		printf("Usage:%s pin on|off\n",argv[0]);
		return 0;
	}
	pin = atoi(argv[1]);
	gpio_pinMode(2,OUTPUT);
	if(strcmp(argv[2],"on")==0)
		gpio_setPin(pin,HIGH);
	else
		gpio_setPin(pin,LOW);
	//putchar(gpio_pinStat(2));
	printf("Mode:%c Value:%c\n",gpio_modeStat(pin),gpio_pinStat(pin));
	return 0;
}

#include <stdio.h>
#include "../../../include/pcduino_gpio.h"
#define BUZZER 6
void pins_init()
{
		gpio_pinMode(BUZZER, OUTPUT);
}
void delay()
{
	int i,j;
	while(i > 10000)	
	{
		for(j=0;j<100;j++)	
			;
		i--;
	}
}
void soundAlarm()
{
		int i;
		for(i = 0;i < 20;i ++)
		{
				gpio_setPin(BUZZER, HIGH);
				delay();
				gpio_setPin(BUZZER, LOW);
				delay();
		}
}
int main(void)
{
	while(1)
	{
	soundAlarm();	
	delay();
	}
	return 0;	
}

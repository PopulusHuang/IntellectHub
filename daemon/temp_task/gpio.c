#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcduino_gpio.h"
#define CMD_SIZE 128
/* set pin mode */
int gpio_pinMode(int pin,int mode)
{
	char cmd[CMD_SIZE];	

	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"echo \"%d\">%sgpio%d",mode,GPIO_MODE_PATH,pin);
	system(cmd);
	return 0;
}
int gpio_setPin(int pin,int value)
{
	char cmd[CMD_SIZE];	

	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"echo \"%d\">%sgpio%d",value,GPIO_PIN_PATH,pin);
	system(cmd);
	return 0;
}
int gpio_pinStat(int pin)
{
	char cmd[CMD_SIZE];	
	char buf[4];
	FILE *fp;
	int value;
	memset(cmd,0,sizeof(cmd));
	memset(buf,0,sizeof(buf));

	sprintf(cmd,"cat %sgpio%d",GPIO_PIN_PATH,pin);
	fp = popen(cmd,"r");
	fgets(buf,3,fp);
	value = atoi(buf);
	pclose(fp);
	return value;
}
void switch_on(int pin)
{
	if(pin == 4)
		gpio_setPin(pin,LOW);
	else
		gpio_setPin(pin,HIGH);
}
void switch_off(int pin)
{
	if(pin == 4)
		gpio_setPin(pin,HIGH);
	else
		gpio_setPin(pin,LOW);
}
/* switch_opt value-- 0:trun off 1:trun on*/
void switch_detect(int pin,int switch_opt)
{
		if(switch_opt == 0) 
			switch_off(pin);
		else
			switch_on(pin);
}

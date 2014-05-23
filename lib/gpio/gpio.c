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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/pcduino_gpio.h"
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
/*
int main(int argc,char **argv)
{
	int pin;	
	int value;	
	if(argc != 3)
	{
		printf("Usage:%s [pin] 0/1\n",argv[0]);	
		exit(0);
	}
	pin = atoi(argv[1]); 
	value = atoi(argv[2]);

	printf("old status:%d\n",gpio_pinStat(pin));

	gpio_setPin(pin,value);
	printf("new status:%d\n",gpio_pinStat(pin));
}
*/

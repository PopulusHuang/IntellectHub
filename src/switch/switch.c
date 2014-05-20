#include <stdio.h>
#include "cgic.h"
#include "pcduino_gpio.h"
#include <stdlib.h>
#include <string.h>
int cgiMain() {
	char hubId[20];
	char hub_stat[10];
	char dev_name[20];
	int pin = -1;
	char pin_value = 'x';
	bzero(hubId,sizeof(hubId));
	bzero(hub_stat,sizeof(hub_stat));
	memset(dev_name,0,sizeof(dev_name));
    	cgiHeaderContentType("text/plain");
#if 1
    	cgiFormString("name",hubId, 20);
	pin = hubId[3]-'0';
	pin++;

	gpio_pinMode(pin,OUTPUT);
	sprintf(dev_name,"pin:%d",pin);
	cgiFormString("status",hub_stat,10);
	if(strcmp(hub_stat,"on")==0)   /* trun off the hub */
	{
	   printf("%s:%d:%s",hubId,pin,"off");
	   if(pin = 4)
	   		gpio_setPin(pin,HIGH);		
	   else 
	   		gpio_setPin(pin,LOW);		
	}
	if(strcmp(hub_stat,"off")==0)  /* trun on the hub */
	{
	   printf("%s:%s:%s",hubId,"电饭锅","on");
	   if(pin == 4) 
	    	gpio_setPin(pin,LOW);  
	   else
	   		gpio_setPin(pin,HIGH);		
	}
#endif
    return 0;
}


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
	gpio_pinMode(pin,OUTPUT);
	sprintf(dev_name,"pin:%d",pin);
	cgiFormString("status",hub_stat,10);
	if(strcmp(hub_stat,"on")==0)
	{
	   printf("%s:%d:%s",hubId,pin,"off");
	   gpio_setPin(pin,LOW);		
#if 0
	   pin_value = gpio_pinStat(pin); 
	   if(pin_value == '0') 
	   {
	    // printf("%s:%s:%s",hubId,"电饭锅","off");
	     printf("%s:%s:%s",hubId,hubId,"off");
	   }
	   else
	     printf("%s:%s:%s",hubId,"电饭锅","on");
#endif
	}
	if(strcmp(hub_stat,"off")==0)
	{
	   printf("%s:%s:%s",hubId,"电饭锅","on");
	   gpio_setPin(pin,HIGH);		
#if 0
	   gpio_setPin(pin,HIGH);		
	   pin_value = gpio_pinStat(pin); 
	   if(pin_value == '1') 
	     printf("%s:%s:%s",hubId,"电饭锅","on");
	   else
	    {
	     printf("%s:%s:%s",hubId,"电饭�","off");
	     //printf("%s:%s:%s",hubId,"空闲","on");
	    }
#endif
	}
#endif
    return 0;
}


#include <stdio.h>
#include "cgic.h"
#include "pcduino_gpio.h"
#include "device_sql.h"
#include <stdlib.h>
#include <string.h>
int cgiMain() {
	char hubId[20];
	char hub_stat[10];
	char dev_name[DEVNAME_SIZE];
	int pin;
	int index;

	sqlite3 *db;	

	memset(hubId,0,sizeof(hubId));
	memset(hub_stat,0,sizeof(hub_stat));
	memset(dev_name,0,sizeof(dev_name));

   	cgiHeaderContentType("text/plain");

   	cgiFormString("name",hubId, 20);
	cgiFormString("status",hub_stat,10);

	int ret = sqlite3_open("data/devices.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}

	index = hubId[3] - '0';

	dev_getNameByHub(db,index,dev_name);

	/* hub control pin from 2 to 4 */
	pin = index + 1;  
	gpio_pinMode(pin,OUTPUT);

//	sprintf(dev_name,"%d",gpio_pinStat(pin));

	if(strcmp(hub_stat,"on")==0)   /* trun off the hub */
	{
	   if(4 == pin)
	   		gpio_setPin(pin,HIGH);		
	   else 
	   		gpio_setPin(pin,LOW);		
	   printf("%s:%s:%s",hubId,dev_name,"off");
	}

	if(strcmp(hub_stat,"off")==0)  /* trun on the hub */
	{
	   if(pin == 4) 
	    	gpio_setPin(pin,LOW);  
	   else
	   		gpio_setPin(pin,HIGH);		
	   printf("%s:%s:%s",hubId,dev_name,"on");
	}
    return 0;
}

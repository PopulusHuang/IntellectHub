#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#include "device_sql.h" 
#define NET_SIZE 50
int cgiMain()
{
	char ip[NET_SIZE];
	char netmask[NET_SIZE];
	char gateway[NET_SIZE];
	
	memset(ip,0,sizeof(ip));
	memset(netmask,0,sizeof(netmask));
	memset(gateway,0,sizeof(gateway));

    cgiHeaderContentType("text/plain");
    cgiFormString("ip",ip,NET_SIZE-1);
	cgiFormString("netmask",netmask,NET_SIZE-1);
	cgiFormString("gateway",gateway,NET_SIZE-1);
  /* open database */ 
  	sqlite3 *db;
	int ret = sqlite3_open("data/devices.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	dev_modifyNet(db,ip,netmask,gateway);
	int n = dev_getNet(db,ip,netmask,gateway);
	printf("%d:%s:%s:%s",n,ip,netmask,gateway);
	return 0;
}

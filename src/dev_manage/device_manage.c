#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#include "device_sql.h"
#define CMD_SIZE  20
#define ID_SIZE   20
#define NAME_SIZE 50
#define POWER_SIZE 20
int cgiMain()
{
#if 1
	int n = 0;
	int ret;
	char cmd[CMD_SIZE];
	char id[ID_SIZE];
	char dev_name[NAME_SIZE];
	char dev_power[POWER_SIZE];
	memset(cmd,0,sizeof(cmd)); memset(id,0,sizeof(id));
	memset(dev_name,0,sizeof(dev_name));
	memset(dev_power,0,sizeof(dev_power));

	cgiHeaderContentType("text/html");
	cgiFormString("cmd",cmd,CMD_SIZE-1);
	cgiFormString("dev_id",id,ID_SIZE-1);
	cgiFormString("dev_name",dev_name,NAME_SIZE-1);
	cgiFormString("dev_power",dev_power,POWER_SIZE-1);

    sqlite3 *db;
	ret = sqlite3_open("data/devices.db",&db);
	int flg = 0;
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	if(strcmp(cmd,"DEL")==0) //delete device 
	{
		n = dev_remove(db,id);		

	}else if(strcmp(cmd,"MOD")==0) //modify device information
	{
		//n = dev_modify(db,"device_tb","4d1d13e0","TV","250");	
		n = dev_modify(db,"device_tb",id,dev_name,dev_power);

	}else if(strcmp(cmd,"REG")==0) //add new device
	{
		n = dev_register(db,id,dev_name,dev_power);		
	}
	if(n < 0)
	{
		printf("%d",n);
	}
	else
	{
		dev_sheet_list(db);
		printf("<div class=\"hint\">当前设备</div>");
		dev_current_list(db);
	}
#else
	int i,n;
	int ret;
	char cmd[CMD_SIZE];
	char id[ID_SIZE];
	char dev_name[NAME_SIZE];
	char dev_power[POWER_SIZE];
    sqlite3 *db;

	cgiHeaderContentType("text/html");
	cgiFormString("cmd",cmd,CMD_SIZE-1);
	cgiFormString("dev_id",id,ID_SIZE-1);
	cgiFormString("dev_name",dev_name,NAME_SIZE-1);
	cgiFormString("dev_power",dev_power,POWER_SIZE-1);
	/*sqlite open*/
	ret = sqlite3_open("data/devices.db",&db);

	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}

	if(dev_modify(db,"device_tb",id,dev_name,dev_power)<0)
	{
		
		printf("-1");
		exit(0);
	}

	dev_sheet_list(db);
	printf("<div class=\"hint\">当前设备</div>");
	dev_current_list(db);
//	printf("n=%d",n);
#endif
	sqlite3_close(db);
	return 0;
}

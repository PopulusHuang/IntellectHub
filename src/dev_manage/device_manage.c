#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#include "device_sql.h"
#define CMD_SIZE  10
#define ID_SIZE   10
#define NAME_SIZE 50
#define POWER_SIZE 10
int cgiMain()
{
	int n = 0;
	int ret;
	char *cmd[CMD_SIZE];
	char *id[ID_SIZE];
	char *dev_name[NAME_SIZE];
	char *dev_power[POWER_SIZE];
    sqlite3 *db;

	cgiHeaderContentType("text/html");
	cgiFormString("cmd",cmd,CMD_SIZE);
	cgiFormString("dev_id",id,ID_SIZE);
	cgiFormString("dev_name",dev_name,NAME_SIZE);
	cgiFormString("dev_power",dev_power,POWER_SIZE);

	ret = sqlite3_open("data/devices.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	if(strcmp(cmd,"DEL")==0)
	{
		n = dev_remove(db,id);		

	}else if(strcmp(cmd,"MOD")==0)
	{
		n = dev_modify(db,id,dev_name,dev_power);	

	}else if(strcmp(cmd,"REG")==0)
	{
		n = dev_register(db,id,dev_name,dev_power);		
	}
	if(n < 0)
		printf("%d",n);
	else
		dev_sheet_list(db);
	return 0;
}

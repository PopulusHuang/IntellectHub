#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sheet_sql.h"
#include "cgic.h"
#include "device_sql.h"
#define BUF_SIZE 1024
int cgiMain()
{
	int i,n;
	int ret;
	char id_buf[10];
	char inputStr[2][VALUE_SIZE];
	char switch_buf[5];
	char enable_buf[5];
	char cmd[BUF_SIZE];
	char dev_name[DEVNAME_SIZE];

	memset(dev_name,0,sizeof(dev_name));
	memset(id_buf,0,sizeof(id_buf));
	memset(inputStr,0,sizeof(inputStr));
	memset(switch_buf,0,sizeof(switch_buf));
	memset(enable_buf,0,sizeof(enable_buf));
    sqlite3 *db;
	/* *.db must be under the root directory of web server,
	 * and the directory mode of *.db must be 777*/
	ret = sqlite3_open("data/devices.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	/* cgic header */
    cgiHeaderContentType("text/plain");
	cgiFormString("hub_id",id_buf,10);
	cgiFormString("inputVal",inputStr[0],20);
	cgiFormString("inputVal2",inputStr[1],20);
	cgiFormString("switch_opt",switch_buf,5);
	cgiFormString("enableBox",enable_buf,5);
	int hub_id=atoi(id_buf);
	n=sheet_row_modify(db,"temp_tb",hub_id,inputStr,switch_buf,enable_buf);
	/*update sheet*/
	if(n==0)
	{
		dev_getNameByHub(db,hub_id,dev_name);
		sheet_row_show(db,"temp_tb",hub_id,dev_name);
	}
	else
		printf("-1");
//	printf("1|hello|world|hi|hi|hi&");
	sqlite3_close(db);
	return 0;
}

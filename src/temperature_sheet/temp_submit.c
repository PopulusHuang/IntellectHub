#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../share/sheet_sql.h"
#include "../../include/cgic.h"
#define BUF_SIZE 1024
int cgiMain()
{
	int i,n;
	int ret;
	char id_buf[10];
	char time_buf[20];
	char switch_buf[5];
	char enable_buf[5];
	char cmd[BUF_SIZE];
	memset(id_buf,0,sizeof(id_buf));
	memset(time_buf,0,sizeof(time_buf));
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
	cgiFormString("inputVal",time_buf,20);
	cgiFormString("switch_opt",switch_buf,5);
	cgiFormString("enableBox",enable_buf,5);
	int hub_id=atoi(id_buf);
	n=sheet_row_modify(db,"temp_tb",hub_id,time_buf,switch_buf,enable_buf);
	/*update sheet*/
	if(n==0)
		sheet_row_show(db,"temp_tb",hub_id,"电视");
	else
		printf("-1");
	sqlite3_close(db);
}

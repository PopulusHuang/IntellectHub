#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "../../include/cgic.h"
#define BUF_SIZE 1024
void insert_row(int hub_id,char *dev_name,char **sqlData)
{
	/* separate each item with '&'*/
	printf("%d|%s|%s|%s|%s&",hub_id,dev_name,sqlData[1],sqlData[2],sqlData[3]);	
}
int timer_sheet_show(sqlite3 *db,int hub_id,char *dev_name)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;

	sprintf(sql,"select * from timer_tb where id='%d';",hub_id);
	/* sqlite3 query, the result are stored in a array 
	 * which was the 'aResult' point to*/
	sqlite3_get_table(db,sql,&aResult,&row,&col,&err);
	int i;

	if(row == 0||col ==0) /* empty result */
	{
		return -1;
	}
	insert_row(hub_id,dev_name,aResult+4);
	return 0;
}
int cgiMain()
{
	int i,n;
	int ret;
    sqlite3 *db;
	/*sqlite open*/
	ret = sqlite3_open("data/timer.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	/* cgic header */
    cgiHeaderContentType("text/plain");
	timer_sheet_show(db,1,"电视");	
	timer_sheet_show(db,2,"电饭锅");
	timer_sheet_show(db,3,"空闲");
	timer_sheet_show(db,4,"电脑");
	sqlite3_close(db);
}

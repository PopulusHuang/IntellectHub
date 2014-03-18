#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#define BUF_SIZE 1024
int timer_sheet_modify(sqlite3 *db,int row,char *time) 
{
	
	char sql[BUF_SIZE];
	char *zErrMsg = NULL;
	int ret;
	memset(sql,0,sizeof(sql));
/*
	sprintf(sql,"update timer_tb set time='%s' \
			switch_opt='%c' enable='%s' where id='%d'",
			time,switch_opt,enable_flg,hub_id);
			*/
	sprintf(sql,"update timer_tb set time='%s' where id='%d'",time,row);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;
}
int main(int argc, const char *argv[])
{
	int i,n=0;
	int ret;
    sqlite3 *db;
	/*sqlite open*/
	ret = sqlite3_open("../../data/timer.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	n=timer_sheet_modify(db,atoi(argv[1]),argv[2]);
	if(n==-1)
		printf("update failed!\n");
	else
		printf("update succeed\n");
	return 0;
}

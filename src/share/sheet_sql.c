#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sheet_sql.h"
#define BUF_SIZE 1024
void insert_row(int hub_id,char *dev_name,char **sqlData)
{
	/* separate each item with '&'*/
	printf("%d|%s|%s|%s|%s|%s&",\
	hub_id,dev_name,sqlData[0],sqlData[1],sqlData[2],sqlData[3]);	
}
int sheet_row_show(sqlite3 *db,char *table,int hub_id,char *dev_name)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;

	sprintf(sql,"select Lvalue,Rvalue,switch_opt,enable from %s where id='%d';",table,hub_id);
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
int sheet_row_modify(sqlite3 *db,char *table,
				int hub_id,char inputStr[][VALUE_SIZE],
				char *switch_opt,char *enable_flg) 
{
	
	char sql[BUF_SIZE];
	char *zErrMsg = NULL;
	int ret;

	/*sqlite open*/
	memset(sql,0,sizeof(sql));
	sprintf(sql,"update %s set Lvalue='%s',Rvalue='%s',\
            switch_opt='%s',enable='%s' where id='%d'",\
			table,inputStr[0],inputStr[1],switch_opt,enable_flg,hub_id);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;
}

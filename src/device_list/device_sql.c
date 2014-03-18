#include <stdio.h>
#include "device_sql.h"
#include <stdlib.h>

#define BUF_SIZE 1024
void insert_row(int index,char *id,char *dev_name,char *dev_power)
{
	printf("<tr><td>%d</td><td>%s</td>",index,id);
	printf("<td><input type=\"text\" class=\"timer_text\" \
			value=\"%s\"></td>",dev_name);
	printf("<td><input type=\"text\" class=\"timer_text\" \
			value=\"%s\"></td>",dev_power);
	printf("<td><label>删除</label><input id=\"DelBox%d\" \
			type=\"checkbox\"></td>",index);
	printf("<td><button class=\"timer_btn\" type=\"button\" \
			onclick=\"dev_update()\">提交</button></td></tr>");
}
int dev_sheet_list(sqlite3 *db)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;

	sprintf(sql,"select * from device_tb;");
	/* sqlite3 query, the result are stored in a array 
	 * which was the 'aResult' point to*/
	sqlite3_get_table(db,sql,&aResult,&row,&col,&err);
	int i,index;

	if(row == 0||col ==0) /* empty result */
	{
		return -1;
	}

	for (i = 3,index=1;i < (row+1)*col;i+=3)
	{
		insert_row(index,aResult[i],aResult[i+1],aResult[i+2]);
		index++;
	}
	sqlite3_free_table(aResult);
	return 0;
}

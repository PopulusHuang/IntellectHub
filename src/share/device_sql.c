#include <stdio.h>
#include "device_sql.h"
#include "read_rfid.h"
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE  500
void insert_row(int index,char *id,char *dev_name,char *dev_power)
{
	printf("<tr><td>%d</td><td id=\"dev_id%d\">%s</td>",index,index,id);
	printf("<td><input id=\"dev_name%d\"type=\"text\" class=\"timer_text\" \
			value=\"%s\"></td>",index,dev_name);
	printf("<td><input id=\"dev_power%d\"type=\"text\" class=\"timer_text\" \
			value=\"%s\"></td>",index,dev_power);
	printf("<td><label>删除</label><input id=\"del_box%d\" \
			type=\"checkbox\"></td>",index);
	printf("<td><button class=\"timer_btn\" type=\"button\" \
			onclick=\"call_devSubmit('%d')\">提交</button></td></tr>",index);
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
int dev_id_isexist(sqlite3 *db,char *id)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	char *err = 0;
	char **aResult;
	char *zErrMsg = NULL;

	sprintf(sql,"select id from device_tb where id='%s'",id);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)  /* id not exist */
	{
		sqlite3_free(zErrMsg);
		return 1;
	}
	return 0;
}
int dev_register(sqlite3 *db,const char *id,
				const char *dev_name,
				const char *dev_power)
{
	char sql[BUF_SIZE];
	char *zErrMsg = NULL;
	int ret;
//	if(dev_id_isexist(db,id)==0) /*id is exist*/
//		return -1;
	sprintf(sql,"insert into device_tb values('%s','%s','%s');",id,dev_name,dev_power);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;
}
int dev_modify(sqlite3 *db,const char *id,
			   const char *dev_name,
			   const char *dev_power)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	char *err = 0;
	char *zErrMsg = NULL;
	char **aResult;

	memset(sql,0,sizeof(sql));
	sprintf(sql,"update device_tb set dev_name='%s' where id='%s'"
			,dev_name,id);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	sprintf(sql,"update device_tb set dev_power='%s' where id='%s'",dev_power,id);

	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	//printf("id=%s;dev_name=%s;dev_power=%s",id,dev_name,dev_power);
	return 0;
}
int dev_remove(sqlite3 *db,const char *id)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;
	char *zErrMsg = NULL;
	
	memset(sql,0,sizeof(sql));
	sprintf(sql,"delete from device_tb where id='%s'",id);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;
}
int dev_check(sqlite3 *db,char *dev_name,int hub_index)
{
	int fd;
	char cardID[9];	

	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;

	memset(cardID,0,sizeof(cardID));
	fd = rfid_open();
	rfid_read(fd,cardID,hub_index);
	
	if(strcmp(cardID,"FF")==0)
	{
		strcpy(dev_name,"Unkown");	
		return 0;
	}
	sprintf(sql,"select dev_name from device_tb where id = '%s';",cardID);
	/* sqlite3 query, the result are stored in a array 
	 * which was the 'aResult' point to*/
	sqlite3_get_table(db,sql,&aResult,&row,&col,&err);
	int i,index;

	if(row == 0||col ==0) /* empty result */
	{
		return -1;
	}

	for (i = 1;i < (row+1)*col;i++)
	{
		strcpy(dev_name,aResult[i]);
	}

	sqlite3_free_table(aResult);
	close(fd);	
	return 0;
}

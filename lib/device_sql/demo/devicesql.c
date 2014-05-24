#include <stdio.h>
#include "device_sql.h"
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
/* list register devices */
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
/* list current devices */
int dev_current_list(sqlite3 *db)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;

	sprintf(sql,"select id,dev_name from currdev_tb;");
	/* sqlite3 query, the result are stored in a array 
	 * which was the 'aResult' point to*/
	sqlite3_get_table(db,sql,&aResult,&row,&col,&err);
	int i,index;

	if(row == 0||col ==0) /* empty result */
	{
		return -1;
	}

	for (i = 2,index=1;i < (row+1)*col;i+=2)
	{
		//insert_row(index,aResult[i],aResult[i+1],"");
		printf("<tr><td>%d</td> <td>%s</td> <td>%s</td></tr>",index,aResult[i],aResult[i+1]);
		index++;
	}
	sqlite3_free_table(aResult);
	return 0;
}
/* check card id ,return 1 if succeed.*/
int dev_id_isexist(sqlite3 *db,char *id)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int row = 0,col = 0;
	char *err = 0;
	char **aResult;
	char *zErrMsg = NULL;

	sprintf(sql,"select id from device_tb where id='%s'",id);
	//ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	sqlite3_get_table(db,sql,&aResult,&row,&col,&err);
	if(row == 0||col ==0) /* empty result */
	{
		return 0;
	}
	return 1;
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
int dev_modify(sqlite3 *db,char *table,char *id,
			   char *dev_name,
			   char *dev_power)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	char *err = 0;
	char *zErrMsg = NULL;
	char **aResult;

	memset(sql,0,sizeof(sql));
	dev_update(db,table,"dev_name",dev_name,"id",id);
	dev_update(db,table,"dev_power",dev_power,"id",id);
#if 0
	sprintf(sql,"update %s set dev_name='%s' where id='%s'"
			,table,dev_name,id);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	if(dev_power == NULL)
		return 0;
	sprintf(sql,"update %s set dev_power='%s' where id='%s'",table,dev_power,id);

	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	#endif
	return 0;
}
int dev_remove(sqlite3 *db,char *id)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;
	char *zErrMsg = NULL;
	
	memset(sql,0,sizeof(sql));
	ret = dev_delete(db,"device_tb","id",id);
	return ret;
}
int dev_delete(sqlite3 *db,char *table,char *sect,char *needle)
{

	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;
	char *zErrMsg = NULL;
	
	memset(sql,0,sizeof(sql));
	sprintf(sql,"delete from %s where  %s='%s'",table,sect,needle);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;
}
/* get device's name by card id */
int dev_getName(sqlite3 *db,char *table,char *id,char *dev_name)
{
	
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;
#if 0
	sprintf(sql,"select dev_name from %s where id='%s';",table,id);
	/* sqlite3 query, the result are stored in a array 
	 * which was the 'aResult' point to*/
	sqlite3_get_table(db,sql,&aResult,&row,&col,&err);

	if(row == 0||col ==0) /* empty result */
	{
		return -1;
	}
	strcpy(dev_name,aResult[1]);
#else
	dev_select(db,table,"dev_name","id",id,dev_name);
#endif
	sqlite3_free_table(aResult);
	return 0;
}
/* get name by hub index */
int dev_getNameByHub(sqlite3 *db,int index,char *dev_name)
{

	char sql[BUF_SIZE];	/* SQL sentene */	
	char hub[4];
	int ret;

	memset(hub,0,sizeof(hub));
	sprintf(hub,"%d",index);
#if 0
	int row,col;
	char *err = 0;
	char **aResult;
	sprintf(sql,"select dev_name from currdev_tb where hub='%d';",index);
	/* sqlite3 query, the result are stored in a array 
	 * which was the 'aResult' point to*/
	sqlite3_get_table(db,sql,&aResult,&row,&col,&err);

	if(row == 0||col ==0) /* empty result */
	{
		return -1;
	}
	strcpy(dev_name,aResult[1]);
	sqlite3_free_table(aResult);
#else
	ret = dev_select(db,"currdev_tb","dev_name","hub",hub,dev_name);
#endif

	return ret;
}
/* update current device on the hub,index:1~3 */
int dev_update(sqlite3 *db,char *table,
			   char *destSect,char *setValue,
			   char *baseSect,char *needle)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	char *err = 0;
	char *zErrMsg = NULL;
	char **aResult;
	

	memset(sql,0,sizeof(sql));
	/* update card id */
	sprintf(sql,"update %s set %s='%s' where %s='%s'",
			table,destSect,setValue,baseSect,needle);

	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	#if 0
	/* update device name */
	sprintf(sql,"update currdev_tb set dev_name='%s' where hub='%d'",
			dev_name,index);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	#endif
	return 0;
}
/*	select 'destSect' base on 'baseSect',
	then storage the result to 'outValue' */
int dev_select(sqlite3 *db,char *table,
				char *destSect,char *baseSect, 
				char *needle,char *outValue)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;

	sprintf(sql,"select %s from  %s  where %s='%s';",destSect,table,baseSect,needle);
	/* sqlite3 query, the result are stored in a array 
	 * which was the 'aResult' point to*/
	sqlite3_get_table(db,sql,&aResult,&row,&col,&err);

	if(row == 0||col ==0) /* empty result */
	{
		return -1;
	}

	strcpy(outValue,aResult[1]);

	sqlite3_free_table(aResult);
	return 0;
}

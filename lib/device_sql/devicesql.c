#include <stdio.h>
#include "device_sql.h"
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE  500
void dev_open(sqlite3 *db,char *path)
{
	int ret = sqlite3_open(path,&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		exit(1);
	}
}
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

	dev_select(db,table,"dev_name","id",id,dev_name);
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

	ret = dev_select(db,"currdev_tb","dev_name","hub",hub,dev_name);

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
		printf("-1");
		return -1;
	}
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
#if 1
/* get the timer task or temperature control task */
int dev_getTask(sqlite3 *db,char *table,HUB_TASK *hubTask,int index)
{
	char needle[5];
	memset(needle,0,sizeof(needle));

	sprintf(needle,"%d",index+1);
	#if 1
 	dev_select(db,table,"Lvalue","id", needle,hubTask[index].Lvalue);
 	dev_select(db,table,"Rvalue","id", needle,hubTask[index].Rvalue);
 	dev_select(db,table,"switch_opt","id", needle,hubTask[index].switch_opt);
 	dev_select(db,table,"enable","id", needle,hubTask[index].enable);
	#endif
	return 0;
}
#endif
int dev_getNet(sqlite3 *db,char *ip,char *netmask,char *gateway)
{
	int ret1,ret2,ret3;
	ret1=dev_select(db,"net_tb","ip","id","1",ip);		
	ret2=dev_select(db,"net_tb","netmask","id","1",netmask);		
	ret3=dev_select(db,"net_tb","gateway","id","1",gateway);		
	if(ret1 < 0||ret2 < 0 ||ret3 < 0)
	{
		return -1;	
	}
	return 0;
}
int dev_modifyNet(sqlite3 *db,char *ip,char *netmask,char *gateway)
{
	int ret1,ret2,ret3;
	ret1=dev_update(db,"net_tb","ip",ip,"id","1");	
	ret2=dev_update(db,"net_tb","netmask",netmask,"id","1");	
	ret3=dev_update(db,"net_tb","gateway",gateway,"id","1");	
	if(ret1 < 0||ret2 < 0 ||ret3 < 0)
	{
		return -1;	
	}
	return 0;
}
int dev_getMQ2(sqlite3 *db,char *outMQ2,char *enable)
{
	int ret,ret2;
	ret = dev_select(db,"MQ2_tb","MQ2","id","1",outMQ2);		
	ret2 = dev_select(db,"MQ2_tb","enable","id","1",enable);		
	if(ret < 0||ret2 < 0) 
	{
		return -1;	
	}
	return 0;
}
int dev_modifyMQ2(sqlite3 *db,char *inMQ2,char *enable)
{
	int ret,ret2;
	ret = dev_update(db,"MQ2_tb","MQ2",inMQ2,"id","1");		
	ret2 = dev_update(db,"MQ2_tb","enable",enable,"id","1");		
	if(ret < 0||ret2 < 0) 
	{
		return -1;	
	}
	return 0;
}

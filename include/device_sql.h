#ifndef _DEVICE_SQL_
#define _DEVICE_SQL_
#include <sqlite3.h>
#define DEVNAME_SIZE 30
#define VALUE_SIZE 128
typedef struct hubtime{
	int hour;
	int min;
	int day;
	int mon;
	int year;
}HUB_TIME;
typedef struct hubtask{
	char Lvalue[VALUE_SIZE];
	char Rvalue[VALUE_SIZE];
	char switch_opt[2];
	char enable[2];
}HUB_TASK;

int dev_update(sqlite3 *db,char *table,
			   char *destSect,char *setValue,
			   char *baseSect,char *needle);
int dev_select(sqlite3 *db,char *table,
				char *destSect,char *baseSect, 
				char *needle,char *outValue);
int dev_delete(sqlite3 *db,char *table,char *sect,char *needle);

int dev_register(sqlite3 *db,const char *id,
				const char *dev_name,
				const char *dev_power);

int dev_modify(sqlite3 *db,char *table,char *id,
			   char*dev_name,
			   char *dev_power);
int dev_remove(sqlite3 *db,char *id);
int dev_sheet_list(sqlite3 *db);
int dev_current_list(sqlite3 *db);
int dev_getName(sqlite3 *db,char *table,char *id,char *dev_name);
int dev_getNameByHub(sqlite3 *db,int index,char *dev_name);
int dev_getTask(sqlite3 *db,char *table,HUB_TASK *hubTask,int index);
void dev_open(sqlite3 *db,char *path);
int dev_getNet(sqlite3 *db,char *ip,char *netmask,char *gateway);
int dev_modifyNet(sqlite3 *db,char *ip,char *netmask,char *gateway);
#endif

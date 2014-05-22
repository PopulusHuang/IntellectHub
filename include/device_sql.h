#ifndef _DEVICE_SQL_
#define _DEVICE_SQL_
#include <sqlite3.h>
#define DEVNAME_SIZE 30
int dev_register(sqlite3 *db,const char *id,
				const char *dev_name,
				const char *dev_power);

int dev_modify(sqlite3 *db,char *table,const char *id,
			   const char*dev_name,
			   const char *dev_power);
int dev_remove(sqlite3 *db,const char *id);
int dev_sheet_list(sqlite3 *db);
int dev_current_list(sqlite3 *db);
int dev_getName(sqlite3 *db,char *table,char *id,char *dev_name);
int dev_update(sqlite3 *db,
			   int index, 	/*hub index*/
			   const char *id,		/*card id */
			   const char *dev_name);
int dev_getNameByHub(sqlite3 *db,int index,char *dev_name);
#endif

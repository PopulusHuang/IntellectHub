#ifndef _DEVICE_SQL_
#define _DEVICE_SQL_
#include <sqlite3.h>

int dev_register(sqlite3 *db,const char *id,
				const char *dev_name,
				const char *dev_power);

int dev_modify(sqlite3 *db,const char *id,
			   const char*dev_name,
			   const char *dev_power);
int dev_remove(sqlite3 *db,const char *id);
#endif

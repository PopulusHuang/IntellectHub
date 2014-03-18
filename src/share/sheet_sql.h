#ifndef _SHEET_SQL_
#define _SHEET_SQL_
#include <sqlite3.h>

void insert_row(int hub_id,char *dev_name,char **sqlData);
int sheet_row_show(sqlite3 *db,char *table,int hub_id,char *dev_name);
int sheet_row_modify(sqlite3 *db,char *table,
				int hub_id,char *inputStr,
				char *switch_opt,char *enable_flg);
#endif

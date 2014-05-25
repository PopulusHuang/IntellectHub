#include <stdio.h>
#include <stdlib.h>
#include "account.h"
int main(void)
{
	sqlite3 *db;
	char user[20];
	char email[20];
	int ret = sqlite3_open("../../../www/cgi-bin/data/hub_user.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	if(account_modify_user(db,"admin","notdoevil@sina.cn","123456")<0)
	{
		printf("modify error!\n");
		exit(1);
	}
	ret = account_get_user(db,user,email);
	if(ret < 0)
	{
		printf("get data error!\n");
		exit(1);
	}
	
	printf("%s:%s\n",user,email);
	return 0;
}

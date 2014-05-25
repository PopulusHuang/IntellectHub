#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#include "account.h"
int cgiMain()
{
	char email[EMAIL_SIZE];
	char username[NAME_SIZE];
	sqlite3 *db;

	memset(email,0,sizeof(email));
	memset(username,0,sizeof(username));
    cgiHeaderContentType("text/plain");
	int ret = sqlite3_open("data/hub_user.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	ret = account_get_user(db,username,email);
	if(ret < 0)
		printf("-1");
	printf("0:%s:%s",username,email);
	return 0;
}

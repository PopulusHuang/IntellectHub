#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#include "account.h"
int cgiMain()
{
	ACCOUNT user;
	char email[EMAIL_SIZE];
    cgiHeaderContentType("text/plain");
    cgiFormString("name",user.name,NAME_SIZE-1);
    cgiFormString("passwd",user.passwd,NAME_SIZE-1);
    cgiFormString("email",email,EMAIL_SIZE-1);
  /* open database */ 
  	sqlite3 *db;
	int ret = sqlite3_open("data/hub_user.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	if(account_verify_passwd(db,user.passwd) != PASSWD_OK)
		printf("-1:");
	if(account_modify_user(db,user.name,email,user.passwd) != USER_OK)
		printf("-2:");
	account_get_user(db,user.name,email);
	printf("0:%s:%s",user.name,email);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#include "account.h"
int cgiMain()
{
	ACCOUNT user;
	char email[EMAIL_SIZE];
	char old_passwd[PASSWD_SIZE];
	int vpasswd,mpasswd;
    cgiHeaderContentType("text/plain");
    cgiFormString("name",user.name,NAME_SIZE-1);
    cgiFormString("passwd",user.passwd,NAME_SIZE-1);
    cgiFormString("old_passwd",old_passwd,PASSWD_SIZE-1);
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
	vpasswd=0;mpasswd=0;
	if(account_verify_passwd(db,old_passwd) != PASSWD_OK)
		vpasswd = -1;
	else if(account_modify_passwd(db,user.name,user.passwd) != PASSWD_OK)
		mpasswd = -2;
	printf("%d:%d",vpasswd,mpasswd);
	return 0;
}

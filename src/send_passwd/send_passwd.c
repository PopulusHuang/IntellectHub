#include <stdio.h>
#include "cgic.h"
#include "session.h"
#include "account.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define CMD_SIZE 256 
int send_passwd(char *name,char *passwd,char *email)
{
	FILE *fp;
	char cmd[CMD_SIZE];
	char ret[5];
	memset(ret,0,sizeof(ret));
	sprintf(cmd,"echo %s:%s |mail -s \"IntellectHub\" %s;echo $?",name,passwd,email);
	fp=popen(cmd,"r");
	if(fgets(ret,4,fp) != NULL)
	{
		if(ret[0]=='0')
		{
			return 0;	
		}
	}
	return -1;
}
int cgiMain() {
	ACCOUNT user;
	int n;
	int ret;
	char name[50];
	char email[50];
	char passwd[20];
    cgiHeaderContentType("text/html");
 /* open database */ 
  sqlite3 *db;
	ret = sqlite3_open("/var/intellect_hub/www/cgi-bin/data/hub_user.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	account_get_user(db,name,email);
	account_get_passwd(db,name,passwd);
	n = send_passwd(name,passwd,email);
	printf("%d",n);
	sqlite3_close(db);
    return 0;
}


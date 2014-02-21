#include <stdio.h>
#include "../../include/cgic.h"
#include "account.h"
#include <string.h>
#include <stdlib.h>
int cgiMain() {
	ACCOUNT user;
	int n;
	int ret;
    cgiHeaderContentType("text/html");
    fprintf(cgiOut, "<HTML><HEAD>\n");
    fprintf(cgiOut, "<TITLE>My CGI</TITLE></HEAD>\n");
    fprintf(cgiOut, "<BODY>");
    cgiFormString("name",user.name, 241);
    cgiFormString("passwd",user.passwd, 241);
#if 1
 /* open database */ 
  sqlite3 *db;
	ret = sqlite3_open("../../data/hub_user.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	n = account_verify(db,user.name,user.passwd); 
	switch(n)
	{
		case USER_OK: printf("<H1>Login Succeed!</H1>\n");
           			fprintf(cgiOut, "<H1>Hello,%s!</H1>",user.name);
					break;
		case USER_ERR: fprintf(cgiOut,
							  "<H1>%s is not exist!</H1>",user.name);
					   break;
		case PASSWD_ERR: printf("<H1>Password error!</H1>");
						 break;
		default :printf("<H1>login failure!</H1>");break;
	}
#endif
    fprintf(cgiOut, "</BODY>\n");
    fprintf(cgiOut, "</HTML>\n");
	sqlite3_close(db);
    return 0;
}

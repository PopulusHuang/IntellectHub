#include <stdio.h>
#include "../../include/cgic.h"
#include "account.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
void setCookie()
{
	time_t timep;
	char  value[20];
	bzero(value,sizeof(value));
	time(&timep);
	sprintf(value,"%d",timep);
	printf("Set-Cookie:FUNNY=%d;path=/\r\n",timep%1000);
}
void show_MainPage()
{
//	printf("<script> location.href=\"../index.html\"; </script>");
	printf("<meta http-equiv=\"refresh\" content=\"0;url=../index.html\">");
}
void show_UserErr()
{
	printf("<script>alert(\"This user is not exist!\")</script>\n");
	/* back to the login page */
	printf("<script> location.href=\"../login.html\"; </script>");
}
void show_PasswdErr()
{
	printf("<script>alert(\"Password error!\")</script>\n");
	printf("<script> location.href=\"../login.html\"; </script>");
}
void show_DefaultErr()
{
	printf("<script>alert(\"Forbid login!\")</script>\n");
	printf("<script> location.href=\"../login.html\"; </script>");
}
int cgiMain() {
	ACCOUNT user;
	int n;
	int ret;
	setCookie();
    cgiHeaderContentType("text/html");
    cgiFormString("name",user.name, 241);
    cgiFormString("passwd",user.passwd, 241);
    fprintf(cgiOut, "<HTML><HEAD>\n");
    fprintf(cgiOut, "<TITLE>Loading...</TITLE>");
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
		case USER_OK:		show_MainPage(); 
							break;
		case USER_ERR: 		show_UserErr(); 
					   		break;
		case PASSWD_ERR:	show_PasswdErr(); 
						 	break;
		default :			show_DefaultErr();
				 			break;
	}
#endif
    fprintf(cgiOut, "</HEAD><BODY>\n");
    fprintf(cgiOut, "</BODY></HTML>\n");
	sqlite3_close(db);
    return 0;
}


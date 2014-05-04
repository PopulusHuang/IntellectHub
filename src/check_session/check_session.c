#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#include "session.h"
int cgiMain()
{
	char session_id[20];
	int n = 0;
	memset(session_id,0,sizeof(session_id));
	cgiHeaderContentType("text/plain");	
	cgiFormString("session_id",session_id,20);
	n = session_check(session_id);
	if(n < 0)
	{
		//session_destory(session_id);	
		printf("session_no:%s",session_id);
		return -1;
	}
	printf("session_ok");
	return 0;
}

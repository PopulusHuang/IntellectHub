#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
#define BUF_SIZE 128
#define TEMP_SIZE 10
int getCurrentTemp()
{
	FILE *fp;
	char cmd[BUF_SIZE];
	char temp_buf[TEMP_SIZE];

	memset(cmd,0,sizeof(cmd));
	memset(temp_buf,0,sizeof(temp_buf));
	sprintf(cmd,"./get_temp");
	fp = popen(cmd,"r");
	if(fgets(temp_buf,TEMP_SIZE-1,fp) == NULL)
		return -1;
	
	return atoi(temp_buf);
}
int cgiMain() {

	char currtemp[TEMP_SIZE];

    cgiHeaderContentType("text/html");
	printf("%d",getCurrentTemp());
    return 0;
}

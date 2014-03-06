#include <stdio.h>
#include "../../include/cgic.h"
#include <stdlib.h>
#include <string.h>
int cgiMain() {
	char *hubId[20];
	char *hub_stat[10];
	char *dev_name[20];
	bzero(hubId,sizeof(hubId));
	bzero(hub_stat,sizeof(hub_stat));
	memset(dev_name,0,sizeof(dev_name));
    cgiHeaderContentType("text/plain");
#if 1
    cgiFormString("name",hubId, 20);
	cgiFormString("status",hub_stat,10);
	if(strcmp(hub_stat,"on")==0)
		printf("%s:%s:%s",hubId,"电饭锅","off");
	if(strcmp(hub_stat,"off")==0)
		printf("%s:%s:%s",hubId,"空闲","on");
#endif
#if 0

    fprintf(cgiOut, "<HTML><HEAD><script>alert('name=%s')</script>\n",name);
    fprintf(cgiOut, "<TITLE>Loading...</TITLE>");
    fprintf(cgiOut, "</HEAD><BODY>on");
    fprintf(cgiOut, "</BODY></HTML>\n");
#endif
    return 0;
}


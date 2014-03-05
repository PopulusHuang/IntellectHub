#include <stdio.h>
#include "../../include/cgic.h"
#include <stdlib.h>
#include <time.h>
int cgiMain() {
	char *name[20];
	bzero(name,sizeof(name));
    cgiHeaderContentType("text/plain");
    cgiFormString("name",name, 19);
	printf("%s:1.加湿器:on",name);
#if 0
    cgiFormString("name",name, 19);
    fprintf(cgiOut, "<HTML><HEAD><script>alert('name=%s')</script>\n",name);
    fprintf(cgiOut, "<TITLE>Loading...</TITLE>");
    fprintf(cgiOut, "</HEAD><BODY>on");
    fprintf(cgiOut, "</BODY></HTML>\n");
#endif
    return 0;
}


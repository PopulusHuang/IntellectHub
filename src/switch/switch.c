#include <stdio.h>
#include "../../include/cgic.h"
#include <stdlib.h>
int cgiMain() {
	char *name[20];
	bzero(name,sizeof(name));
    cgiHeaderContentType("text/plain");
#if 0
    cgiFormString("name",name, 19);
	printf("%s:1.加湿器:on",name);
    cgiFormString("name",name, 19);
#endif
	printf("call cgi");
#if 0

    fprintf(cgiOut, "<HTML><HEAD><script>alert('name=%s')</script>\n",name);
    fprintf(cgiOut, "<TITLE>Loading...</TITLE>");
    fprintf(cgiOut, "</HEAD><BODY>on");
    fprintf(cgiOut, "</BODY></HTML>\n");
#endif
    return 0;
}


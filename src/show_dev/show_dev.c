#include <stdio.h>
#include "../../include/cgic.h"
#include <stdlib.h>
void show_hub_stat(char *hubId,char *switch_stat ,char *dev_name)
{
	printf("<form>");
	printf("<img id=\"%s\" name=\"%s\" \ 
			src=\"images/bulb%s.png\" width=\"81\" height=\"81\"\ 
			onclick=\"call_server('%s')\">",
			hubId,hubId,switch_stat,hubId);
	printf("<p id=\"dev%s\">1.%s</p>",hubId,dev_name);
	printf("</form>");
}
int cgiMain() {
	char *name[20];
	bzero(name,sizeof(name));
    cgiHeaderContentType("text/html");

	printf("<div class=\"bulb_lf\">");
	show_hub_stat("hub1","on","电脑");
	show_hub_stat("hub2","on","电视");
	printf("</div>");

	printf("<div class=\"bulb_rt\">");
	show_hub_stat("hub3","off","空闲");
	show_hub_stat("hub4","off","饮水机");
	printf("</div>");
    return 0;
}

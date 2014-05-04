#include <stdio.h>
#include "../../include/cgic.h"
#include <stdlib.h>
void show_hub_stat(char *hubId,char *switch_stat ,char *dev_name,char *num)
{
	printf("<form>");
	printf("<img id=\"%s\" name=\"%s\" \ 
			src=\"images/bulb%s.png\" width=\"81\" height=\"81\"\ 
			onclick=\"call_server('%s')\">",
			hubId,hubId,switch_stat,hubId);
	printf("<br><label>%s.</label><label id=\"dev%s\">%s</label><p></p>",num,hubId,dev_name);
	printf("</form>");
}
int cgiMain() {
	char *name[20];
	bzero(name,sizeof(name));
    cgiHeaderContentType("text/html");

	printf("<div class=\"bulb_lf\">");
	show_hub_stat("hub1","on","电脑","1");
	show_hub_stat("hub3","on","电视","3");
	printf("</div>");

	printf("<div class=\"bulb_rt\">");
	show_hub_stat("hub2","off","空闲","2");
	show_hub_stat("hub4","off","饮水机","4");
	printf("</div>");
    return 0;
}

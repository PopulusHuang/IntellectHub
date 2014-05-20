#include <stdio.h>
#include "cgic.h"
#include "pcduino_gpio.h"
#include <string.h>
#include <stdlib.h>
#define HUB1 2
#define HUB2 3
#define HUB3 4
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
	char name[20];
	char hubswitch[2][4] = {"off","on"};
	int stat1,stat2,stat3;		
//	bzero(name,sizeof(name));
	memset(name,0,sizeof(name));

	stat1 = gpio_pinStat(HUB1);
	stat2 = gpio_pinStat(HUB2);
	stat3 = !gpio_pinStat(HUB3);

    cgiHeaderContentType("text/html");

	printf("<div class=\"bulb_lf\">");
	show_hub_stat("hub1",hubswitch[stat1],"电脑","1");
	show_hub_stat("hub3",hubswitch[stat3],"电视","3");
	printf("</div>");

	printf("<div class=\"bulb_rt\">");
	show_hub_stat("hub2",hubswitch[stat2],"Computer","2");
	printf("</div>");
    return 0;
}

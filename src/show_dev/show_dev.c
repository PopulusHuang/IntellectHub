#include <stdio.h>
#include "cgic.h"
#include "pcduino_gpio.h"
#include "device_sql.h"
#include <string.h>
#include <stdlib.h>
#define HUB1 2
#define HUB2 3
#define HUB3 4
void show_hub_stat(char *hubId,char *switch_stat,char *dev_name,char *num)
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
	char dev_name1[DEVNAME_SIZE];
	char dev_name2[DEVNAME_SIZE];
	char dev_name3[DEVNAME_SIZE];
	char hubswitch[2][4] = {"off","on"};
	int stat1,stat2,stat3;		
	sqlite3 *db;

    cgiHeaderContentType("text/html");

	memset(dev_name1,0,sizeof(dev_name1));
	memset(dev_name2,0,sizeof(dev_name2));
	memset(dev_name3,0,sizeof(dev_name3));

	int ret = sqlite3_open("data/devices.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	
	/* get the hub's switch status */
	stat1 = gpio_pinStat(HUB1);
	stat2 = gpio_pinStat(HUB2);
	stat3 = !gpio_pinStat(HUB3);
	/* get the device's name */
	dev_getNameByHub(db,1,dev_name1);
	dev_getNameByHub(db,2,dev_name2);
	dev_getNameByHub(db,3,dev_name3);

	
	printf("<div class=\"bulb_lf\">");
	show_hub_stat("hub1",hubswitch[stat1],dev_name1,"1");
	show_hub_stat("hub3",hubswitch[stat3],dev_name3,"3");
	printf("</div>");

	printf("<div class=\"bulb_rt\">");
	show_hub_stat("hub2",hubswitch[stat2],dev_name2,"2");
	printf("</div>");
    return 0;
}

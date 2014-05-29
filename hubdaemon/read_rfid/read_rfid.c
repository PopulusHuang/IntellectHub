#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h> 
#include <string.h>
#include "device_sql.h"
#define BUF_SIZE 256
#define SERIAL_DEV    "/dev/ttyS1"
int serial_cfg(int serialfd,int baud)
{
	int status;
	struct termios opt;

    /* Fetch the current port settings */
	tcgetattr(serialfd,&opt);
    /* Flush the port's buffers (in and out) before 
       we start using it */
	tcflush(serialfd,TCIOFLUSH);
	/* Set the input and output baud rates */	
	cfsetispeed(&opt,baud);
	cfsetospeed(&opt,baud);

   status = tcsetattr(serialfd, TCSANOW, &opt);
	if (status != 0)
	{       
		perror("tcsetattr");
		return -1;    
	}   
	printf("status=%d\n",status);
	tcflush(serialfd,TCIOFLUSH);

	/*  8,1,N*/
	opt.c_cflag &= ~PARENB; /* no parity */	
	opt.c_cflag &= ~CSTOPB; /* one stop bit */
	opt.c_cflag &= ~CSIZE;	/* clear frame size info */
	opt.c_cflag |= CS8;		/* 8 bit frames */

	opt.c_cflag |= (CLOCAL | CREAD);

	opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	opt.c_oflag &= ~OPOST;
	opt.c_oflag &= ~(ONLCR | OCRNL);

	opt.c_iflag &= ~(ICRNL | INLCR);
	opt.c_iflag &= ~(IXON | IXOFF | IXANY);

	tcflush(serialfd, TCIOFLUSH);
	opt.c_cc[VTIME] = 0;
	opt.c_cc[VMIN] = 1;

	/* push it back to the system */
	if(tcsetattr(serialfd, TCSANOW, &opt) != 0)
	{
		 perror("serial error");	
		 return -1;
	}
	printf("Configure complete!\n");
	return 0;
}
int read_card(int serialfd ,int RdIndex,char *cardID)
{
	char Reader[3] = {0xc1,0xc2,0xc3};

	write(serialfd,Reader+RdIndex,1);
	sleep(1);
	read(serialfd,cardID,8);

	return 0;
}
void enable_uart2(void)
{
	system("echo 3 > /sys/devices/virtual/misc/gpio/mode/gpio0");	
	system("echo 3 > /sys/devices/virtual/misc/gpio/mode/gpio1");	
}
int main(void)
{
	int i,ret = 0;
	int serialfd;
	int state;
	sqlite3 *db;

	enable_uart2();

	serialfd=open(SERIAL_DEV,O_RDWR|O_NONBLOCK);
	if (serialfd < 0)
	{
		perror("open error");	
		exit(1);
	}
	/* Serial port configure */
	state = serial_cfg(serialfd,B57600);
	if(state == -1)
	{
		perror("Serial configure error!");
		exit(1);
	}
	/* Flush the buffer. */
	tcflush(serialfd, TCIOFLUSH);

	
	printf("read_card...\n");
	ret = sqlite3_open("/var/intellect_hub/www/cgi-bin/data/devices.db",&db);

	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	char cardID[10];
	char dev_name[30];
	char hub[4];
	int n;
	memset(cardID,0,sizeof(cardID));
	memset(dev_name,0,sizeof(dev_name));
	memset(hub,0,sizeof(hub));
	while(1)
	{
		for(i = 0;i < 3;i++)
		{
			read_card(serialfd,i,cardID);
		//	printf("%s\n",cardID);

			if((strcmp(cardID,"FF") == 0)||(strcmp(cardID,"") == 0)) //has no card
			{
				strcpy(cardID,"null");
				strcpy(dev_name,"null");
			}
			else
			{
				if(dev_id_isexist(db,cardID))
				{
					//card exist,then get the device's name
					dev_getName(db,"device_tb",cardID,dev_name);
				}
				else	/* undefine device */
				{
					strcpy(dev_name,"unkown");	
				}
			}
			/* update the current devices */
			sprintf(hub,"%d",i+1);
			dev_update(db,"currdev_tb","id",cardID,"hub",hub);	
			dev_update(db,"currdev_tb","dev_name",dev_name,"hub",hub);	

			memset(cardID,0,sizeof(cardID));
			memset(dev_name,0,sizeof(dev_name));
			sleep(2);
		}
	}

	close(serialfd);
	return 0;
}

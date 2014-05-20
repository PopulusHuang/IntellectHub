#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "pcduino_gpio.h"
#define BUF_SIZE 100

int gpio_pinMode(int pinID,int mode)
{
        int fd;
        fd = gpio_open(pinID,GPIO_MODE_PATH);
        gpio_write(fd,mode);
        return 0;
}
/* open a gpio file */
int gpio_open(int pinID,char *gpio_path)
{
        char path[BUF_SIZE];
        int fd;
        memset(path,0,sizeof(path));
        sprintf(path,"%sgpio%d",gpio_path,pinID);
        /* open pin mode file */
        fd = open(path,O_RDWR);
if (fd < 0)
        {
                fprintf(stderr,"open %s error!",path);
                exit(0);
        }
        return fd;
}
/* set gpio value */
int gpio_setPin(int pinID,int value)
{
        int fd;
        fd = gpio_open(pinID,GPIO_PIN_PATH);
        gpio_write(fd,value);
}
/* get pin status */
int gpio_pinStat(int pinID)
{
        int fd;
        char c = 'x';
		int val = -1;
        fd = gpio_open(pinID,GPIO_PIN_PATH);
        c = gpio_read(fd);
		val = c - '0';
		if(val > 1)		/* 0:low power ; 1:high power*/
			exit(1);
        return val;
}
/* get pin mode */
int gpio_modeStat(int pinID)
{
        int fd;
        char c = 'x';
		int val = -1;
        fd = gpio_open(pinID,GPIO_MODE_PATH);
        c = gpio_read(fd);
		val = c - '0';
		if(val > 1)		/*val-- 0:INPUT MODE ; 1:OUTPUT MODE*/
			exit(1);
        return val;
}
/* write a gpio file */
int gpio_write(int fd,int value)
{
        char buf[4];
        int len = sizeof(buf);
        memset(buf,0,len);
        sprintf(buf,"%d",value);
        /* Make sure at the top of the file */
        lseek(fd,0,SEEK_SET);
        write(fd,buf,len);
        return 0;
}
/* read a gpio file */
char gpio_read(int fd)
{
        char data[4];
        int len = sizeof(data);

        memset(data,0,len);
        lseek(fd,0,SEEK_SET);
        read(fd,data,len);

        return data[0];
}

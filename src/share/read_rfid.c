#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h> 
#include <string.h>
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
	printf("configure complete\n");
	return 0;

}
int rfid_read(int serialfd ,char *cardID,int hub_index)
{
	char Reader[3] = {0xc1,0xc2,0xc3};

	write(serialfd,Reader+hub_index,1);
	usleep(1000);
	read(serialfd,cardID,8);

	return 0;
}
void enable_uart2(void)
{
	system("echo 3 > /sys/devices/virtual/misc/gpio/mode/gpio0");	
	system("echo 3 > /sys/devices/virtual/misc/gpio/mode/gpio1");	
}
int rfid_open(void)
{
	int i;
	int serialfd;
	int state;
	
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

	return serialfd;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <termios.h>
#include <errno.h>
#include <linux/poll.h>

#define DS1 23
#define DS2 24
#define DS3 25
#define DS4 26

FILE *pFile, *qFile;
int sw1,sw2,sw3,sw4;		
int dip_fd;
int fd1,fd2;
unsigned int mask = 0;
struct pollfd fds[1];
char buf_rx[1500];
char buf_tx[1500];
char buf[1500];
int cmp;

void comparefiles(){
qFile=fopen("receive.txt","r");
fgets(buf,sizeof(buf),qFile);
cmp=strcmp(buf_tx,buf);		
if(cmp==0)
	printf("Sent data is received correctly\n");
else
	printf("error in receiving\n");
fclose(qFile);
}

int dip_open(){
	int fd;
	system("mknod /dev/dip-sw c 244 0");
	fd = open("/dev/dip-sw", O_RDWR, 0);
	if(fd<0)
	{
		printf("Cannot open device\r\n");
		return -1;
	}
	return fd;	
}


int uart_dip()
{
	fds[0].fd = dip_fd;
	fds[0].events=POLLIN;
	/*To get the dip switch status*/
	sw1 = ioctl(dip_fd,DS1,0);
	sw2 = ioctl(dip_fd,DS2,0);
	sw3 = ioctl(dip_fd,DS3,0);
	sw4 = ioctl(dip_fd,DS4,0);

	if(sw2==0 && sw3==0 && sw4==0){
		system("stty -F /dev/ttymxc0 '9600'");
		system("stty -F /dev/ttymxc2 '9600'");
		printf("baud rate is 9600\n");
	 }
	 else if(sw2==0 && sw3==0 && sw4==1){
		system("stty -F /dev/ttymxc0 '19200'");
		system("stty -F /dev/ttymxc2 '19200'");
		printf("baud rate is 19200\n");	
	 }	
	 else if(sw2==0 && sw3==1 && sw4==0){
		system("stty -F /dev/ttymxc0 '19200'");
		system("stty -F /dev/ttymxc2 '19200'");
 		printf("baud rate is 19200\n");
	 }
	 else if(sw2==0 && sw3==1 && sw4==1){
		system("stty -F /dev/ttymxc0 '38400'");
		system("stty -F /dev/ttymxc2 '38400'");
		printf("baud rate is 38400\n");
	 }
	else if(sw2==1 && sw3==0 && sw4==0){
		system("stty -F /dev/ttymxc0 '57600'");
		system("stty -F /dev/ttymxc2 '57600'");
		printf("baud rate is 57600\n");
	 }
	 else if(sw2==1 && sw3==0 && sw4==1){
		system("stty -F /dev/ttymxc0 '115200'");
		system("stty -F /dev/ttymxc2 '115200'");
		printf("baud rate is 115200\n");
	 }
	 else if(sw2==1 && sw3==1 && sw4==0){
		system("stty -F /dev/ttymxc0 '2000000'");
		system("stty -F /dev/ttymxc2 '2000000'");
		printf("baud rate is 2000000\n");
	 }
	 else if(sw2==1 && sw3==1 && sw4==1){
		system("stty -F /dev/ttymxc0 '3000000'");
		system("stty -F /dev/ttymxc2 '3000000'");
		printf("baud rate is 3000000\n");
	 }
	if(sw1==1) /*uart3 is sender and uart1 is receiver*/
	{	
		init_uart();
		printf("Uart3 is sending: %s to Uart1\n",buf_tx);
		int result = write(fd2, (char *) buf_tx, sizeof(buf_tx));
    			if (result == -1) {
       				printf("Error: %s\n", strerror(errno));
       				 return -1;
    			} 
			else {
       		 		printf("%d bytes sent to UART1\n", result);
   			 }
    		usleep(1860000);
		int op=read(fd1, buf_rx, sizeof(buf_rx));
		if (op==-1) {
        		printf("Error: %s\n", strerror(errno));
        		return -1;
   		 } 
		else {	 
				printf("%d bytes received to UART1\n",op);
        			printf("Uart1 received: %s from Uart3\n", buf_rx);
				qFile=fopen("receive.txt","w+");
				fputs(buf_rx,qFile);
				fclose(qFile);
				comparefiles();	
    			}
		close(fd1);
		close(fd2);
	}
 	if(sw1==0) /*uart  is sender and uart3 is receiver*/
 	{
		init_uart();
		printf("Uart1 is sending: %s to Uart3\n",buf_tx);
		int result = write(fd1, (char *) buf_tx, sizeof(buf_tx));
       			if (result == -1) {
           			printf("Error: %s\n", strerror(errno));
            			return -1;
       			 } 
			else {
       				 printf("%d bytes sent to Uart3\n", result);
      			  }
		usleep(1860000);
		int op=read(fd2, buf_rx, sizeof(buf_rx));
		if (op==-1) {
        		printf("Error: %s\n", strerror(errno));
        		return -1;
   		 } 
		else {
				printf("%d bytes received to UART3\n",op);
        			printf("UART3 received: %s\n", buf_rx); 
				qFile=fopen("receive.txt","w+");
				fputs(buf_rx,qFile);
				fclose(qFile);
				comparefiles();				
   		 }
		close(fd1);
		close(fd2);
	}
	POLL : mask = poll(fds,1);
		if(fds[0].revents & POLLIN)
			uart_dip();
		else
			goto POLL;

}
int init_uart()
{
	fd1=open("/dev/ttymxc0", O_RDWR|O_NOCTTY);
	if(fd1<0)
	{
		printf("\n  Error! in Opening ttymxc\n");
		return -1;
	}
	fd2=open("/dev/ttymxc2", O_RDWR|O_NOCTTY);
   	if(fd2<0)
	{
		printf("\n  Error! in Opening ttymxc\n");
		return -1;
	}
}
int main()
{ 
	dip_fd=dip_open();
	init_uart();
	pFile=fopen("send.txt","r");
	if(pFile==NULL)
		perror("File open error\n");
	fgets(buf_tx,sizeof(buf_tx),pFile);
	struct termios tty;
	if(tcgetattr(fd1, &tty) != 0) {
     	 	printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      	return 1;
	}
	if(tcgetattr(fd2, &tty) != 0) {
     	 	printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      	return 1;
	}
	/*c_cflag=Control Mode flags*/
  	tty.c_cflag &=~PARENB; /*Clear parity bit, disabling parity*/
  	tty.c_cflag &=~CSTOPB; /*Clear stop field, only one stop bit used in communication (most common)*/
  	tty.c_cflag &=~CSIZE; /*Clear all bits that set the data size*/
  	tty.c_cflag |=CS8; /*8 bits per byte */
  	tty.c_cflag &=~CRTSCTS; /*Disable RTS/CTS hardware flow control*/ 
 	tty.c_cflag |=CREAD | CLOCAL; /*Turn on READ & ignore ctrl lines (CLOCAL = 1)*/

 	tty.c_lflag &=~ICANON; /*Disable canonical mode*/
  	tty.c_lflag &=~ECHO; /*Disable echo*/
  	tty.c_lflag &=~ECHOE; /*Disable erasure*/
  	tty.c_lflag &=~ECHONL; /*Disable new-line echo*/
  	tty.c_lflag &=~ISIG; /*Disable interpretation of INTR, QUIT and SUSP*/
  	tty.c_iflag &=~(IXON | IXOFF | IXANY); /*Turn off s/w flow ctrl*/
  	tty.c_iflag &=~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); /*Disable any 	special handling of received bytes*/

  	tty.c_oflag &=~OPOST; /*Prevent special interpretation of output bytes (e.g. newline chars)*/
  	tty.c_oflag &=~ONLCR; /*Prevent conversion of newline to carriage return/line feed*/

  	/*Set in/out baud rate to be 9600*/
  	cfsetispeed(&tty,9600);
        cfsetospeed(&tty,9600);
	
  	/*save tty settings also checking for error*/
  	if (tcsetattr(fd1, TCSANOW, &tty) != 0) {
   		 printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
		}
	tcflush(fd1, TCIFLUSH);
	if (tcsetattr(fd2, TCSANOW, &tty) != 0) {
   		 printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
		}
	tcflush(fd2,TCIFLUSH);
	/*call the uart function*/
	close(fd1);
	close(fd2);
	uart_dip();

}

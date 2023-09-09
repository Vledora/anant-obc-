#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdint.h>
#include<sys/ioctl.h>
#include<linux/i2c-dev.h>
#include<sys/stat.h>

#define i2c "/dev/i2c-2"

uint8_t slave_addr = 0b1101000;
uint8_t data = 0x00;
uint8_t reply;
uint8_t *time = data;

static int write(int fd, const void *buf, size_t count){
	if((cb = write(fd,buf,count))>0){
		print("%s file opened to write",__FILENAME__);
		return 0;
	}
	else {perror("error");
		return(-1);}
}

static int read(int fd, const void *buf, size_t count){
	if((cb = write(fd,buf,count))>0){
		print("%s file opened to read",__FILENAME__);
		return 0;
	}
	else {perror("error");
		return(-1);}
}

static int time(){
	int fd;
	void *buf;
	fd = open(i2c,O_APPEND);
	
	if ((ioctl(fd,I2C_SLAVE,slave_addr))<0)
	{
		perror("error");
		close(fd);
		return(-1);
	}
	uint8_t *reply;
	for(int i;i<3,i++){
	write(fd,time+i,1);
	read(fd,reply+i,1);}
	
	close(fd);
	return 0;
}
int main(){
	time();
	FILE *fp;
	char time[3];
	time = reply;
	fp = fopen("time.txt","w");
	fwrite(time,1,sizeof(time),fp);
	fclose(fp);
}

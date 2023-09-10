#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdint.h>
#include<sys/ioctl.h>
#include<linux/i2c-dev.h>
#include<sys/stat.h>
#include<math.h>

#define i2c "/dev/i2c-2"

uint8_t slave_addr = 0b1101000;
uint8_t data = 0x00;
uint8_t reply[3];

int BcdToDecimal(uint8_t arg){
	int ans = 0;
    for(int i=0;i<8;++i){
	if(i<=3){
	    ans += pow(i, 2) * ((arg >> i) % 2);
	}
	else{
	    ans += 10 * (pow(i-4, 2) * ((arg >> i) % 2));
	}
    }
    return ans;
}
static int write(int fd, const void *buf, size_t count){
	if((cb = write(fd,buf,count))>0){
		print("file opened to write");
		return 0;
	}
	else {perror("error");
		return(-1);}
}

static int read(int fd, const void *buf, size_t count){
	if((cb = write(fd,buf,count))>0){
		print("file opened to read");
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
		return(-1);
	}
	uint8_t *reply;
	write(fd,data,1);
	for(int i;i<3,i++){
	read(fd,reply+i,1);}
	int s,m,h;
	s = bcd_to_decimal(reply[1]);
	m = bcd_to_decimal(reply[2]);
	h = bcd_to_decimal(reply[3]);
	snprintf(time, 10,"%dh:%dm:%ds",h,m,s);
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

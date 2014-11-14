#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include<fcntl.h>
#include<stdio.h>

struct temp {
	int key;
	int value;
};

int
main(void) {
    int fd;
    struct temp t1;
    t1.key = 101;
    t1.value = 202;
    fd = open("/devices/pseudo/ioctl_impl_drv@0:0", O_RDONLY);
    if(ioctl(fd, 1, &t1) == -1) {
        printf("Error with case 1");
    }
   
    if(ioctl(fd, 0, &t1) == -1) {
    	printf("Error with case 0");
    }
   
    printf("Value of t1.key = %d\n", t1.key);
    printf("Value of t1.value = %d\n", t1.value);
    //printf("device status %x\n", status);
    return(0);
}

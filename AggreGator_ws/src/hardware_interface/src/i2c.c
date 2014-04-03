#include "i2c.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define max_read_bytes 41;
#define max_write_bytes 40;
#define filename "/dev/i2c-1";

char* read_i2c(int address, int size) 
{
	int file; //the "file" that will be used to interface with the i2c bus
    char* read_buffer = (char*) malloc(max_read_bytes);
	read_buffer[0] = 1; //1 means data is not valid
	
	if (size > max_read_bytes)
	{
		printf("Cannot read that many bytes!");
		return read_buffer;
	}
	
	char filename[40] = "/dev/i2c-1";
	if ((file = open(filename,O_RDWR)) < 0) {
        printf("Failed to open the bus.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
		/*error_buffer = g_strerror(errno);
            printf(error_buffer);*/
        return read_buffer;
    }
	
	if (ioctl(file,I2C_SLAVE,address) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
		/*error_buffer = g_strerror(errno);
            printf(error_buffer);*/
        return read_buffer;
    }
	
	if (read(file,read_buffer+1,size) != size) {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to read from the i2c bus.\n");
            /*error_buffer = g_strerror(errno);
            printf(error_buffer);*/
            printf("\n\n");
			read_buffer[0] = 1; //1 means data is not valid
			return read_buffer;
        } else {
			//for(int i = size; i >0; i--) //shift all data right one bit
			//	read_buffer[i] = read_buffer[i-1];
			read_buffer[0] = 0;//0 for valid data, 1 else
            return read_buffer;
	 }
	 
	 else
		return read_buffer;
}	

char* readfromreg_i2c(int address, char reg_ptr_addr, int size)
{
	int file; //the "file" that will be used to interface with the i2c bus
    char* read_buffer = (char*) malloc(max_read_bytes);
	read_buffer[0] = 1; //1 means data is not valid
	
	if (size > max_read_bytes)
	{
		printf("Cannot read that many bytes!");
		return read_buffer;
	}
	
	char filename[40] = "/dev/i2c-1";
	if ((file = open(filename,O_RDWR)) < 0) {
        printf("Failed to open the bus.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
		/*error_buffer = g_strerror(errno);
            printf(error_buffer);*/
        return read_buffer;
    }
	
	if (ioctl(file,I2C_SLAVE,address) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
		/*error_buffer = g_strerror(errno);
            printf(error_buffer);*/
        return read_buffer;
    }
	//set the register to be read from
    if(write(file,reg_ptr_addr,1) != 1) {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus.\n\n");
   //     error_buffer = g_strerror(errno);
//        printf(error_buffer);
		return read_buffer;
    }
	
	if (read(file,read_buffer+1,size) != size) {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to read from the i2c bus.\n");
            /*error_buffer = g_strerror(errno);
            printf(error_buffer);*/
            printf("\n\n");
			read_buffer[0] = 1; //1 means data is not valid
			return read_buffer;
        } else {
			//for(int i = size; i >0; i--) //shift all data right one bit
			//	read_buffer[i] = read_buffer[i-1];
			read_buffer[0] = 0;//0 for valid data, 1 else
            return read_buffer;
	 }
	 
	 else
		return read_buffer;
}	

int writetoreg_i2c(int address, char reg_ptr_addr, int size, char* data)
{
	int file; //the "file" that will be used to interface with the i2c bus
	if (size > max_write_bytes)
	{
		printf("Cannot write that many bytes!");
		return 1;
	}
	
	char write_buffer[max_write_bytes];
	char filename[40] = "/dev/i2c-1";
	if ((file = open(filename,O_RDWR)) < 0) {
        printf("Failed to open the bus.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
		/*error_buffer = g_strerror(errno);
            printf(error_buffer);*/
        return 1;
    }
	
	if (ioctl(file,I2C_SLAVE,address) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
		/*error_buffer = g_strerror(errno);
            printf(error_buffer);*/
        return 1;
    }
	
	write_buffer[0] = reg_ptr_addr;
	
	for(int i = 1; i <= size; i++) //copy data into write_buffer
		write_buffer[i]=data[i-1];
	
    if(write(file, write_buffer, size+1) != size+1) {
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to write to the i2c bus.\n\n");
		return 1;
    }  
	
	return 0;
}

int write_i2c(int address, int size, char* data)
{
	int file; //the "file" that will be used to interface with the i2c bus
	if (size > max_write_bytes)
	{
		printf("Cannot write that many bytes!");
		return 1;
	}
	
	char write_buffer[max_write_bytes];

	char filename[40] = "/dev/i2c-1";
	if ((file = open(filename,O_RDWR)) < 0) {
        printf("Failed to open the bus.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
		/*error_buffer = g_strerror(errno);
            printf(error_buffer);*/
        return 1;
    }
	
	if (ioctl(file,I2C_SLAVE,address) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
		/*error_buffer = g_strerror(errno);
            printf(error_buffer);*/
        return 1;
    }
	
    if(write(file, data, size) != size) {
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to write to the i2c bus.\n\n");
		return 1;
    }  
	
	return 0;
}





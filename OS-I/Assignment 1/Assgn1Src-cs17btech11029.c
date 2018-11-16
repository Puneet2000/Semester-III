/*
author@ Puneet Mangla 
roll_no@ CS17BTECH11029

forking and shared memory
*/

// necessary libraries
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(int argc , char* argv[]){

	if (argc<2){ // if no command is specified then show error that arguments too less
		printf("Too less arguments !\n");
		return 1;
	}

	char* command[argc]; // command to be executed
	int i;
	for (i = 0; i < argc-1; i++){ // filling in command array with commands
		command[i]=argv[i+1];
	}
	command[argc-1]=NULL;

	pid_t pid; // process id
	pid = fork(); // fork a child process

	if (pid < 0){
		fprintf(stderr,"Fork Failed"); // fork failure
		return 1;
	}
	else if (pid==0){ // it is a child process

		char* name = "OS"; // name of the shared memory
		int shm_fd; // file descriptor to shared memory

		// create a shared memory object
		shm_fd = shm_open(name,O_CREAT | O_RDWR,0666);
		ftruncate(shm_fd,sizeof(struct timeval)); // allocate memory to store struct timeval

		struct timeval* before_execution; // pointer to structure storing before execution timestamp
		before_execution = mmap(0,sizeof(struct timeval),PROT_WRITE,MAP_SHARED,shm_fd,0); // memory map shared memory object

		gettimeofday(before_execution,NULL); // store before execution timestamp
		execvp(command[0],command); // execute the command

	}
	else{
		int status=0;
		char* name = "OS"; // name of the shared memory
		wait(&status); // wait for the child process to terminate

		if (status!=0){
			printf("Error executing the command ( check if command entered is correct )\n");
			shm_unlink(name); // unlink or destory shared memory
			return 1;
		}

		struct timeval after_execution; // structure storing after execution timestamp in address space of parent
		gettimeofday(&after_execution,NULL); // get after execution timestamp

		
		int shm_fd; // file discriptor to shared memory

		struct timeval* before_execution; // get before execution time of command

		shm_fd = shm_open(name,O_RDONLY,0666); // give read only permission
		before_execution = mmap(0,sizeof(struct timeval),PROT_READ,MAP_SHARED,shm_fd,0); // get pointer to before execution structure via mmap

		long int sec = after_execution.tv_sec - before_execution->tv_sec; // get elapsed seconds
		long int usec = after_execution.tv_usec - before_execution->tv_usec; // get elapsed micro seconds

		double etime =  (double)sec + (usec/1000000.0); // get elapsed time in seconds
		printf("Elapsed time: %lf\n",etime); // print on console

		shm_unlink(name); // unlink or destory shared memory
	}
	return 0;
}
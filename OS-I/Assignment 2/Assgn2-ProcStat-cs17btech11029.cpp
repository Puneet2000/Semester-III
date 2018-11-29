/*
Author@ Puneet Mangla
CS17BTECH11029
*/

// necessary libraries
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <algorithm>
#include <math.h>
using namespace std;

int main(int argc , char* argv[]){


	if (argc != 2){ // check if name of the input file is provided or not
		cout<<"Too less arguments\n";
		return 1;
	}

	string number; // number representing in the input file
	ifstream infile; // input file stream object to extract numbers from input file
	infile.open(argv[1]); // open the file
	infile >> number; // take first number , it will be the value of N i.e number of observations

	long int N ;
	int status;
	N = stol(number); // convert to long integer

	double *a; // array of observations
	a = (double*)malloc(N*sizeof(double));
	long int i=0;
	while (infile >> number){ // while array is not full or input file is not empty 
		a[i] = stod(number); // put values in the array
		i++;
	}

	// child_pid -  PID of forked child
	// wpid - PID of child that just terminated
	pid_t child_pid , wpid; 

	char name[] = {'O','S','I'}; // name of the shared memory object
	long int shm_fd , SIZE = 3*sizeof(double); // shared memory descriptor and its size ( for three quantities)

	shm_fd = shm_open(name,O_CREAT | O_RDWR,0666); // create shared memory
	ftruncate(shm_fd,SIZE); // allocate size

	for (long int i=0 ;i<3 ;i++){ // run three child process
		child_pid = fork(); // fork one child process

		if (child_pid < 0){ // check if child process failed or not
			cout<<"Failed to fork chid process "<<i+1<<endl;
			break;
		}

		if (child_pid==0 && i==0){ // for first child process assign task to calculate average

			double avg =0.0;
			for (long int j=0 ;j<N;j++){ // sum all numbers in array
				avg+=a[j]/N; // divide by total number of observations
			}

			double* stat;
			stat = (double*)mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0); // link the process with shared memory 
			*stat = avg; // put the average in first sizeof(double) bytes of shared memory
			free(a);

			return 0; // exit successfully from process
		}
		else if (child_pid==0 && i==1){ // for second child assign task of standard deviation

			double avg_x=0.0 ,avg_xx =0.0;

			for (long int j=0 ;j<N;j++){ // calculate E[X^2] and E[X]
				avg_x+=a[j]/N;
				avg_xx += (a[j]*a[j])/N;
			}

			double std = sqrt(avg_xx - (avg_x*avg_x)); // from variance calculate the standard deviation

			double* stat;
			stat = (double*)mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0); // link the process with shared memory 
			*(stat+1) = std; // put the average in middle sizeof(double) bytes of shared memory
			free(a);

			return 0; // exit successfully from process

		}
		else if (child_pid==0 && i==2){ //task of median for the third child 

			double median =0.0;

			sort(a,a+N); // sort the array copy the process has

			if (N%2==1) // find the median of the sorted array
				median = a[N/2];
			else
				median = (a[(N/2)-1] + a[N/2])/2.0;

			double* stat;
			stat = (double*)mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0); // link the process with shared memory 
			*(stat+2) = median; // put the average in last sizeof(double) bytes of shared memory
			free(a);

			return 0; // exit successfully from process

		}
	}

	while ((wpid = wait(&status)) > 0); // wait for all child processes to complete

	double* stats;
	stats = (double*)mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0); // link the parent process with shared memory

	ofstream ofile; // output file stream object
	ofile.open("pro_stat_out.txt"); // create a output file

	ofile<<"The average value is "<<*stats<<endl; // put data in output file in specified format
	ofile<<"The standard deviation value is "<<*(stats+1)<<endl;
	ofile<<"The median value is "<<*(stats+2)<<endl;
	free(a);

	return 0;
}

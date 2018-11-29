/*
Author@ Puneet Mangla
CS17BTECH11029
*/

// necessary libraries

#include <pthread.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

double mean,med,stdev; // global variables to store information so that threads can access them.
long int N; // total number of observations

void *average(void *param){ // runner function to calculate average

	double* arr = (double*)param; // type cast parameters to array of observations
	mean = 0.0;

	for (long int i=0;i<N;i++){ // calculate mean by sum of observations by number of observations
		mean+=arr[i]/N;
	}
}

void *median(void* param){ // runner function to calculate median

	double* arr = (double*)param; // type cast parameters to array of observations
	double *a; // dummy array to sort so that there are no data conflicts
	a = (double*)malloc(N*sizeof(double));

	med = 0.0;
	for (long int i=0;i<N;i++){ // copy the contents of actual array to dummy array
		a[i] = arr[i];
	}

	sort(a,a+N); // sort array

	if (N%2==1) // find median of sorted array
		med = a[N/2];
	else
		med = (a[(N/2)-1] + a[N/2])/2.0;

	free(a);
}

void *standard_dev(void* param){ // runner function to calculate standard deviation

	double* arr = (double*)param; // type cast parameters to array of observations
	double avg_x=0.0 ,avg_xx =0.0;

	for (long int j=0 ;j<N;j++){ // calculate mean
		avg_x +=arr[j]/N;
		avg_xx += (arr[j]*arr[j])/N;
	}

	stdev = sqrt(avg_xx - (avg_x*avg_x)); // find standard deviation by square root
}

int main(int argc,char* argv[]){

	if (argc < 2){ // check if name of the input file is provided or not
		cout<<"Too less arguments\n";
		return 1;
	}

	string number; // number representing in the input file
	ifstream infile; // input file stream object to extract numbers from input file
	infile.open(argv[1]); // open the file
	infile >> number; // take first number , it will be the value of N i.e number of observations

	long int status;
	N = stol(number); // convert to long integer

	double *a; // array of observations
	a = (double*)malloc(N*sizeof(double));
	long int i=0;
	while (infile >> number && i<N){ // while array is not full or input file is not empty 
		a[i] = stod(number); // put values in the array
		i++;
	}

	pthread_t tid[3]; // three threads to be created
	pthread_attr_t attr[3]; // corresponding attributes

	for (long int i=0;i<3;i++){ // set attributes , create thread and assign runner functions

		pthread_attr_init(&attr[i]); // set the default attributes to threads

		if(i==0)
			pthread_create(&tid[i] ,&attr[i],average,a); // assign to calculate average
		else if(i==1)
			pthread_create(&tid[i] ,&attr[i],standard_dev,a); // standard deviation
		else if(i==2)
			pthread_create(&tid[i] ,&attr[i],median,a); // median

	}

	for (long int i=0;i<3;i++) // wait for all threads to finish
		pthread_join(tid[i],NULL);

	ofstream ofile; // output file stream object
	ofile.open("thread_stat_out.txt"); // create a output file

	ofile<<"The average value is "<<mean<<endl; // put data in output file in specified format
	ofile<<"The standard deviation value is "<<stdev<<endl;
	ofile<<"The median value is "<<med<<endl;
	free(a);
	return 0;
}
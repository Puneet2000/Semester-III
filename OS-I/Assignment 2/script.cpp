#include <iostream>
#include <fstream>
#include<time.h> 
using namespace std;

int main (int argc , char* argv[]){

	int N = stoi(argv[1]);

	ofstream ofile;
	ofile.open("in.txt"); 
	ofile<<N<<endl;

	srand(time(0));

	for(int i = 0; i<N; i++) 
        ofile<<rand()/10000000<<" "; 

	return 0;
}
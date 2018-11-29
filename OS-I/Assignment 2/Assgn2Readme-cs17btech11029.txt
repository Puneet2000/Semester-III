## Multi-Process & Multi-Threaded Computation of Statistics

**The goal of this assignment is to compute some statistics over a sequence of input numbers using multiple threads, processes and compare the times taken each of them.**

Author : Puneet Mangla ( CS17BTECH11029 )

----------------------------------------------------------------------------

### Instructions to create input file

1. The input file format should be as follows-
	a) The first file should contain number (N) of observations.
	b) From next line N space seperated numbers (real or integers).

	Example : 
	5
	1 2 3 4 5

2. Create a input file with any name <input_file_name>.txt

-----------------------------------------------------------------------------

### Instructions to generate input file

1. Make a file script.cpp and paste the following code -

		#include <iostream>
		#include <fstream>
		#include <time.h> 
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

2. Complile the script using following command -
		$ g++ script.cpp -o script

3. Generate input file of arbitary size by running the binary-
		$ ./script <N>

		Example:
		$ ./script 1000000

4. A file name 'in.txt' will be generated which can be used for testing.

--------------------------------------------------------------------------------

### Instructions to calculate statistics using Multi-Processing

1. Compile Assgn2-ProcStat-cs17btech11029.cpp file using following command -
		$ g++ Assgn2-ProcStat-cs17btech11029.cpp -lrt -o pro

2. Run the binary to generate output file -
		$ ./pro <input_file_name>.txt

		Example:
		$ ./pro in.txt

3. An Output file will be generated 'pro_stat_out.txt' containing the statistics of input file using multi-processing.

---------------------------------------------------------------------------------

### Instructions to calculate statistics using Multi-Threading

1. Compile Assgn2-ThStat-cs17btech11029.cpp file using following command -
		$ g++ Assgn2-ThcStat-cs17btech11029.cpp -pthread -o th

2. Run the binary to generate output file -
		$ ./th <input_file_name>.txt

		Example:
		$ ./th in.txt

3. An Output file will be generated 'thread_stat_out.txt' containing the statistics of input file using multi-threading.

----------------------------------------------------------------------------------

### Instructions to compare generated files and find the time taken

1. Run the following files to compare generated output files
		$ diff pro_stat_out.txt thread_stat_out.txt

2. If no errors occur then files are same.

3. To check the time taken run the following commands-
		$ time ./pro in.txt
		$ time ./th in.txt

4. See the contents of file :
		$ cat pro_stat_out.txt
		$ cat thread_stat_out.txt

------------------------------------------------------------------------------------

### A Complete Example 

$ g++ script.cpp -o script
$ ./script 3000000
$ g++ Assgn2-ProcStat-cs17btech11029.cpp -lrt -o pro
$ time ./pro in.txt

real	0m0.937s
user	0m0.957s
sys	0m0.016s

$ g++ Assgn2-ThcStat-cs17btech11029.cpp -pthread -o th
$ time ./th in.txt

real	0m0.929s
user	0m0.924s
sys	0m0.036s

$ diff pro_stat_out.txt thread_stat_out.txt
$ cat pro_stat_out.txt
The average value is 106.89
The standard deviation value is 62.0033
The median value is 107

------------------------------------------------------------------------------------


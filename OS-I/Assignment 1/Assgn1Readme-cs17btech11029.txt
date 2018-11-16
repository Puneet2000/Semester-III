## Multi-Process Computation of Execution Time

**This assignment is about calculation the execution time of commands using multi-processing and inter-process communication**

----------------------------------------------------------------

### Instructions :

1. Complile the Assgn1Src-cs17btech11029.c file using following command : 
	gcc Assgn1Src-cs17btech11029.c -lrt -o time

2.  Run the binary file generated as follows :
	./time <command to be executed>s

3. If the file shows permission denied ,do as follows :
	sudo chmod +x time
	./time <command to be executed>

----------------------------------------------------------------

### Syntax Examples :

1. Listing
	./time ls

2. Listing with flags
	./time ls -lh

3. Making folder
	./time mkdir <folder name>

4. Deleting Folder
	./time rmdir <folder name>

----------------------------------------------------------------

### Sample Outputs : 

1. 	$ ./time ls
	a.out				 Assgn1Report-cs17btech11029.pdf  graph.py
	Assgn1Readme-cs17btech11029.txt  Assgn1Src-cs17btech11029.c	  outputs
	Assgn1Report-cs17btech11029.odt  data.odt
	Elapsed time: 0.003250

2. 	$ ./time ls -l
	total 724
	-rwxr-xr-x 1 puneet puneet  16552 Nov 16 15:58 a.out
	-rw-r--r-- 1 puneet puneet    675 Nov 16 17:57 Assgn1Readme-cs17btech11029.txt
	-rw-rw-r-- 1 puneet puneet 320487 Nov 16 18:13 Assgn1Report-cs17btech11029.odt
	-rw-r--r-- 1 puneet puneet 360856 Nov 16 18:13 Assgn1Report-cs17btech11029.pdf
	-rw-r--r-- 1 puneet puneet   2730 Nov 16 15:59 Assgn1Src-cs17btech11029.c
	-rw-rw-r-- 1 puneet puneet  14969 Nov 16 14:06 data.odt
	-rw-r--r-- 1 puneet puneet    930 Nov 16 14:01 graph.py
	drwxr-xr-x 2 puneet puneet   4096 Nov 16 14:45 outputs
	Elapsed time: 0.005194

-----------------------------------------------------------------
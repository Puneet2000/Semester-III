### Multi-Process Computation of Execution Time

**This assignment is about calculation the execution time of commands using multi-processing and inter-process communication**

### Instructions

- Complile the Assgn1Src-cs17btech11029.c file using following command : 
	gcc Assgn1Src-cs17btech11029.c -lrt -o time

- Run the binary file generated as follows :
	./time <command to be executed>

- If the file shows permission denied ,do as follows :
	sudo chmod +x time
	./time <command to be executed>

**Examples**

- Listing
	./time ls

- Listing with flags
	./time ls -lh

- Making folder
	./time mkdir <folder name>

- Deleting Folder
	./time rmdir <folder name>


**Note : If you run only ./time without any arguments , the time elapsed printed on console gives time of overall program**
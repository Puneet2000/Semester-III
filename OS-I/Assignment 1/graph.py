
import matplotlib.pyplot as plt 
  
# line 1 points 
x1 = [0.484,0.989,1.2,3.2,5,7,9,12.4] 
y1 = [0.047712,0.065284,0.063200,0.125659,0.183118,0.242681,0.292735,0.349051] 
# plotting the line 1 points  
plt.plot(x1, y1, label = "tar -czvf") 
  
# line 2 points 
x2 = [0.484,0.989,1.2,3.2,5,7,9,12.4]
y2 = [0.086233,
0.154285,
0.173590,
0.386538,
0.622225,
0.799513,
1.034310,
1.457238]  
# plotting the line 2 points  
plt.plot(x2, y2, label = "bzip2") 

x3 = [0.484,0.989,1.2,3.2,5,7,9,12.4]
y3 = [0.046635,
0.060013,
0.071418,
0.117602,
0.190658,
0.232482,
0.288150,
0.353596]  

plt.plot(x3, y3, label = "gzip",color='red') 
# naming the x axis 
plt.xlabel('Size of file in MB') 
# naming the y axis 
plt.ylabel('Average Time taken (seconds) ') 
# giving a title to my graph 
plt.title('tar command on files of different size') 
  
# show a legend on the plot 
plt.legend() 
  
# function to show the plot 
plt.savefig('./compress.jpg') 

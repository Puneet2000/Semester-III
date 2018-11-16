
import matplotlib.pyplot as plt 
  
# line 1 points 
x1 = [1,2,3,4,5,6,7,8,9,10] 
y1 = [0.003119,
0.003768,
0.004391,
 0.005010,
 0.005793,
0.006787,
0.007500,
 0.008261,
 0.008966,
0.009659] 
# plotting the line 1 points  
plt.plot(x1, y1) 
"""
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
"""
# naming the x axis 
plt.xlabel('Number of programs') 
# naming the y axis 
plt.ylabel('Average Time taken (seconds) ') 
# giving a title to my graph 
plt.title('N same programs in sequential manner') 
  
# show a legend on the plot 
  
# function to show the plot 
plt.savefig('./program.jpg') 

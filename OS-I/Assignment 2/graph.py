
import matplotlib.pyplot as plt 
plt.figure(figsize=(10,8)) 
# line 1 points 
x1 = [1,2,3,4,5,6,7,8,9,10] 
y1 = [329217,
632890,
917599,
1236864,
1604291,
1871016,
2231678,
2552499,
2846629,
3215614
] 
# plotting the line 1 points  
plt.plot(x1, y1,label = "multi-processing") 

#line 2 points 
x2 = [1,2,3,4,5,6,7,8,9,10]
y2 = [301243,
 610490,
943925,
1233439,
1554632,
1885521,
2212864,
2548772,
2855864,
3195434
]  
# plotting the line 2 points  
plt.plot(x2, y2, label = "multi-threading") 
"""
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


plt.xlabel('Number of observations in million') 
# naming the y axis 
plt.ylabel('Average Time taken (micro - seconds) ') 
# giving a title to my graph 
plt.title('Multi-threading vs multi-processing for large data') 
  
# show a legend on the plot 
plt.legend() 

# function to show the plot 
plt.savefig('./program.jpg') 

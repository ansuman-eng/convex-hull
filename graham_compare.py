import matplotlib.pyplot as plt
from time import time
x_ip =[]
y_ip =[]
scatter_x=[]
scatter_y=[]

#SCATTER THE INPUT POINTS
with open('input_points.txt') as f:
	for line in f:
		#print(line,len(line))
		x,y = line.split('\n')[0].split(' ')
		x = float(x)
		y = float(y)

		scatter_x.append(x)
		scatter_y.append(y)
plt.scatter(scatter_x,scatter_y)

#PLOT THE LINES
with open('graham_compare.txt') as f:
	for line in f:
		#print(line,len(line))
		x,y = line.split('\n')[0].split(' ')
		x = float(x)
		y = float(y)

		x_ip.append(x)
		y_ip.append(y)
#PLOT THE FIRST LINE
plt.plot(x_ip[0:2],y_ip[0:2], color='red', marker='o')
#PLOT THE SECOND LINE
plt.plot(x_ip[1:3],y_ip[1:3], color='red', marker='o')
#TO GET A UNIQUE NAME
t = time()
plt.savefig('compare'+str(t)+'.png')
import matplotlib.pyplot as plt

scatter_x_ip =[]
scatter_y_ip =[]
with open('input_points.txt') as f:
	for line in f:
		#print(line,len(line))
		x,y = line.split('\n')[0].split(' ')
		x = float(x)
		y = float(y)

		scatter_x_ip.append(x)
		scatter_y_ip.append(y)
plt.scatter(scatter_x_ip,scatter_y_ip,s=4)

scatter_x_op =[]
scatter_y_op =[]
with open('output_points.txt') as f:
	for line in f:
		#print(line,len(line))
		x,y = line.split('\n')[0].split(' ')
		x = float(x)
		y = float(y)

		scatter_x_op.append(x)
		scatter_y_op.append(y)
plt.scatter(scatter_x_op,scatter_y_op,s=4)

plt.savefig('output'+str(len(scatter_x_op))+'.png')
plt.close()
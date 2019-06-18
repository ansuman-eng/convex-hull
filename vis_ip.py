scatter_x =[]
scatter_y =[]
with open('input_points.txt') as f:
	for line in f:
		#print(line,len(line))
		x,y = line.split('\n')[0].split(' ')
		x = float(x)
		y = float(y)

		scatter_x.append(x)
		scatter_y.append(y)
import matplotlib.pyplot as plt
plt.scatter(scatter_x,scatter_y, s=4)

plt.savefig('input.png')
plt.show(block=False)
plt.pause(3)
plt.close()
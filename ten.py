import numpy as np
import matplotlib.pyplot as plt

nlogn=[6719,380,56]
nsquare=[19233,185,1]
# Numbers of pairs of bars you want
N = 3

# Data on X-axis

# Specify the values of blue bars (height)
blue_bar = nlogn[::-1]
# Specify the values of orange bars (height)
orange_bar = nsquare[::-1]

# Position of bars on x-axis
ind = np.arange(N)

# Figure size
plt.figure(figsize=(10,5))

# Width of a bar 
width = 0.3       

# Plotting
plt.bar(ind, blue_bar , width, label='nlogn')
plt.bar(ind + width, orange_bar, width, label='nsquared')

plt.xlabel('Number of elements in input array')
plt.ylabel('Time in micro seconds')
plt.title('Time Comparison')

# xticks()
# First argument - A list of positions at which ticks should be placed
# Second argument -  A list of labels to place at the given locations
plt.xticks(ind + width / 2, ('10', '100', '1000'))

# Finding the best position for legends and putting it
plt.legend(loc='best')
plt.show()
'''
import matplotlib.pyplot as plt
# line 1 points
x1 = nlogn[::-1]
y1 = [10,100,1000,10000,50000]
# plotting the line 1 points 
plt.plot(y1, x1, label = "nlogn")
# line 2 points
x2 = nsquare[::-1]
y2 = [10,100,1000,10000,50000]
# plotting the line 2 points 
plt.plot(y2, x2, label = "n squared")
plt.ylabel('Time in microseconds')
# Set the y axis label of the current axis.
plt.xlabel('')
# Set a title of the current axes.
plt.title('Comparing nlogn with n squared ')
# show a legend on the plot
plt.legend()
# Display a figure.
plt.show()
'''
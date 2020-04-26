import matplotlib.pyplot as plt
import csv
import numpy as np

y1 = []
y2 = []
y3 = []
x = []

with open('output.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[0]))
        y1.append(float(row[1]))
        y2.append(float(row[2]))
        y3.append(float(row[3]))


x = np.array(x)

plt.plot(x, y1, '#1DB954', label = "Divide And Conquer Algorithm") # plotting t, a separately 
plt.plot(x, y2, '#00A2FF', label = "Karatsuba Algorithm") # plotting t, b separately 
plt.plot(x, y3, '#FF004D', label = "Grade School Algorithm") # plotting t, c separately 


plt.legend()
plt.grid()     

plt.xlabel("Length")
plt.ylabel("Time (ms)")

plt.show()




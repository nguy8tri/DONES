import array as arr
import numpy as np
import scipy.linalg as sc
import matplotlib.pyplot as plt
import matplotlib.colors
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.ticker import LinearLocator

import sys
sys.path.append("build")
import translate

print("Hello, and welcome to DONES, a Thermal Network Solver")

# Dimension
N = int(input("What is the dimension of your object? "))

# Dimensions
xLength = float(input("What is the length of your object? "))
yLength = float(input("What is the height of your object? "))
Dx = float(input("What is your length-step value? "))
Dy = float(input("What is your height-step value? "))

l = arr.array('f', [xLength, yLength, Dx, Dy])

# Conductivity

k = float(input("What is the thermal conductivity of your material? "))

# Boundary Conditions
h = arr.array('f', [0, 0, 0, 0])
T = arr.array('f', [0, 0, 0, 0])

print("You will now be prompted for boundary conditions")
print("The boundary conditions will be in this order: Up, Down, Left, Right")

h[0] = float(input("Boundary 1: Heat Transfer Coefficient (0 if insulated or constant temperature condition): "))
T[0] = float(input("Boundary 1: Surface/Ambient Temperature (0 if insulated): "))
h[1] = float(input("Boundary 2: Heat Transfer Coefficient (0 if insulated or constant temperature condition): "))
T[1] = float(input("Boundary 2: Surface/Ambient Temperature (0 if insulated): "))
h[2] = float(input("Boundary 3: Heat Transfer Coefficient (0 if insulated or constant temperature condition): "))
T[2] = float(input("Boundary 3: Surface/Ambient Temperature (0 if insulated): "))
h[3] = float(input("Boundary 4: Heat Transfer Coefficient (0 if insulated or constant temperature condition): "))
T[3] = float(input("Boundary 4: Surface/Ambient Temperature (0 if insulated): "))

# Call Analysis -> Returns the array of T distributions, NOT System

distro = translate.t(N, l, k, h, T)

width = int(round(l[0] / l[2])) + 1
height = int(round(l[1] / l[3])) + 1

# print(str(width) + " " + str(height) + " " + str(len(distro)))

min = distro[0]
max = distro[0]

object = np.zeros((height, width))
for i in range(height):
    for j in range(width):
        object[i, j] = distro[i * width + j]
        if object[i, j] > max:
            max = object[i, j]
        if object[i, j] < min:
            min = object[i, j]

x = np.arange(0, xLength + Dx, Dx)
y = np.arange(0, yLength + Dy, Dy)

# print(x)
# print(y)

fig = plt.figure(1)
x, y = np.meshgrid(x, y)
cf = plt.contourf(x,y,object, cmap='inferno', levels = np.linspace(min, max, 20))
norm= matplotlib.colors.Normalize(min, max)
sm = plt.cm.ScalarMappable(norm=norm, cmap = cf.cmap)
sm.set_array([])
cb = fig.colorbar(sm, ticks=cf.levels)
cb.set_label("Temperature (K)")
'''
cbar.locator = LinearLocator(numticks=11)
cbar.update_ticks()
'''
plt.xlabel('Length (m)')
plt.ylabel('Width (m)')
plt.title('Temperature Distribution')
plt.show()

for i in range(height):
    for j in range(width):
        print("%-8.3f "% (object[i, j]), end=' ')
    print()

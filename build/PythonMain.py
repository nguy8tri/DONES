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
dims = ["length", "height", "depth"]
l = arr.array('f', [])

for i in range(N):
    l.append(float(input("What is the " + dims[i] + " of your object? ")))
    l.append(float(input("What is your " + dims[i] + "-step value? ")))

systemDims = arr.array('i', [])
for i in range(N):
    systemDims.append(int(round(l[2 * i] / l[2 * i + 1])) + 1)

# Conductivity

k = float(input("What is the thermal conductivity of your material? "))

# Boundary Conditions
h = arr.array('f', [])
T = arr.array('f', [])

print("You will now be prompted for boundary conditions")
print("The boundary conditions will be in this order: Left, Right, Up, Down, Above, Below")
for i in range(2 * N):
    h.append(float(input("Boundary 1: Heat Transfer Coefficient (0 if insulated or -1 for constant temperature condition): ")))
    T.append(float(input("Boundary 1: Surface/Ambient Temperature (0 if insulated): ")))

# Call Analysis -> Returns the array of T distributions, NOT System

distro = translate.t(N, l, systemDims, k, h, T)

# print(str(width) + " " + str(height) + " " + str(len(distro)))

min = distro[0]
max = distro[0]

width = systemDims[0]
height = systemDims[1]

object = np.zeros((height, width))
for i in range(height):
    for j in range(width):
        object[i, j] = distro[(height - i - 1) * width + j]
        if object[i, j] > max:
            max = object[i, j]
        if object[i, j] < min:
            min = object[i, j]

x = np.linspace(0, l[0], width)
y = np.linspace(0, l[2], height)

print(x)
print(y)

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

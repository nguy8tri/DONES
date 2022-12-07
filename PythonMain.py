import array as arr
import numpy as np
import scipy.linalg as sc
import matplotlib as plot


import sys
sys.path.append("/home/tri_nguyen/DONES/build")
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

width = int(round(l[0] / l[2]))
height = int(round(l[1] / l[3]))

object = np.zeros((width, height))
for i in range(height):
    for j in range(width):
        object[i, j] = distro[i * width + j]




for i in range(height):
    for j in range(width):
        print("%-8.3f "% (object[i, j]), end=' ')
    print()
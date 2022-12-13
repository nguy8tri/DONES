# DONES: DONES Open-Source Numerical Euler Solver

This is a primative thermal network simulation software. This software is meant for students to learn about simple FEA machines and how FEA works in general. It uses rectangular meshes and calculated heat distributions with the aid of a gaussian solver.

# Running DONES

- Make sure you have a Linux System of Subsystem, Windows Subsystem for Linux (WSL) for example, which can be downloaded withn Visual Studio Code (VS Code).
- Install g++. On Ubuntu: `sudo apt install g++`
- Install make. On Ubuntu: `sudo apt install make`
- Install cmake. On Ubuntu: `sudo apt install cmake`
- Install python3.8. On Ubuntu: `sudo apt install python3.8` and `sudo apt install python3.8-dev`
- Install git. On Ubuntu: `sudo apt install git`. Make sure you sign in.
- Clone this repositiory. On your linux terminal: `git clone https://github.com/nguy8tri/DONES`. Then, `cd dones`.
- Then, we need to compile our C++ files. On Ubuntu:
    `mkdir build`
    `cd build`
    `cmake ..`
- Then, `make`, and `python3.8 PythonMain.py`, you will be guided with the interface. To rerun the program, you only need to repeat `python3.8 PythonMain.py`

# Specifications

- **Dimensions**: All objects are 3D, but certain objects can be modeled/simulated as 2D or 1D objects. Our simulation can handle:
    - [ ] 1 Dimension
    - [X] 2 Dimensions
    - [ ] 3 Dimensions

- **Boundary Conditions**: At the edges of objects, boundary conditions are required to fully define the system. Our simulation can handle:
    - [X] Convective
        - [X] Insulating
    - [X] Constant Temperature
    - [ ] Constant Flux

- **Boundary Cases**: For any given point in a mesh that is near a boundary, the heat flux at that point is different and must be handeled per case. Our simulation can handle:
    - [X] Corners
    - [X] Convex Edges
    - [ ] Concave Edges

- **Shapes**: Different Shapes, or rather shapes within different coordinate systems effects the heat distribution. Our simulation can handle:
    - [X] Rectangular
    - [ ] Cylindrical
    - [ ] Spherical
    - [ ] General Rectangular

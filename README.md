# DONES: DONES Open-Source Numerical Euler Solver

This is a primative thermal network simulation software. This software is meant for students to learn about simple FEA machines and how FEA works in general. It uses rectangular meshes and calculated heat distributions with the aid of a gaussian solver.

# Running DONES

- Make sure you have a Linux System of Subsystem, Windows Subsystem for Linux (WSL) for example, which can be downloaded withn Visual Studio Code (VS Code).
- Install g++. On your linux terminal: `sudo apt install g++`
- Install make. On your linux terminal: `sudo apt install make`
- Install git. On your linux terminal: `sudo apt install git`. Make sure you sign in.
- Clone this repositiory. On your linux terminal: `git clone https://github.com/nguy8tri/DONES`. Then, `cd dones`.
- Run `make` and `./dones`, and it should give a distribution based on entries inside of main (Interface coming soon).

# Specifications

- **Dimensions**: All objects are 3D, but certain objects can be simulated as 2D or 1D objects. Our simulation can handle:
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
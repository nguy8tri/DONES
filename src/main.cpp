#include <iostream>
#include <math.h>

#include "system.hpp";
#include "solve.hpp";

int main(int argc, char** argv) {
    /*
    float arr[9] = 
    {3, 8, 2, 
    2, 5, -3, 
    1, 2, -2};
    float sol[3] = {-5, 0, -1};
    Matrix *A = new Matrix(arr, 3, 3);
    Vector *b = new Vector(sol);
    // b->Display();
    A->GaussianSolve(*b).Display();
    // A->Display();
    */
    
    int N = 2;
    int xLength = 9;
    int yLength = 9;
    float Dx = 3;
    float Dy = 3;
    int k = 60;
    struct BC boundaries[4];
    for(int i = 0; i < 4; i++) {
        boundaries[i] = {250, 25};
    }
    int width = (int) std::round(xLength / Dx);
    int height = (int) std::round(yLength / Dy);
    Matrix *m = new Matrix((float *) malloc(width * height * sizeof(float)), height, width);
    SystemND *system = new SystemND(m, boundaries, k, N);
    system->Dx = Dx;
    system->Dy = Dy;
    std::set<int> exclude;
    Solve(*system, exclude)->distro->Display();
    
    return 0;
}
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
    
    int N = 1;
    float xLength = 200; // 0.284988;
    float yLength = 200; // M_PI * .0127;
    float Dx = 10;
    float Dy = 10; // M_PI * .0127;
    int k = 167;
    struct BC boundaries[4];
    for(int i = 0; i < 4; i++) {
        boundaries[i] = {37.165, 26};
    }
    int width = (int) std::round(xLength / Dx);
    int height = (int) std::round(yLength / Dy);
    // std::cout << xLength << " " << Dx << " " << xLength / Dx << " " << std::round(xLength / Dx) << std::endl;
    std::set<int> exclude;
    float *array = (float *) malloc(width * height * sizeof(float));
    for(int i = 0; i < height; i++) {
        array[i * width] = 70.491667;
        exclude.insert(i * width);
    }
    
    Matrix *m = new Matrix(array, height, width);
    
    SystemND *system = new SystemND(m, boundaries, k, N);
    system->Dx = Dx;
    system->Dy = Dy;

    Solve(*system, exclude)->distro->Display();
    
    return 0;
}
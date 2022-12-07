#include "main.hpp"

std::vector<float> translate(int N, std::vector<float> dims, float k, std::vector<float> h, std::vector<float> T) {
    BC *boundaries = (BC *) malloc(4 * sizeof(BC));
    for(int i = 0; i < 4; i++) {
        boundaries[i].h = h[i];
        boundaries[i].temperature = T[i];
    }
    /*
    std::cout << "N: " << N << std::endl;
    std::cout << "k: " << k << std::endl;
    for(int i = 0; i < dims.size(); i++) {
        std::cout << "Dims " << i << ": " << dims.at(i) << std::endl;
    }
    for(int i = 0; i < dims.size(); i++) {
        std::cout << "h " << i << ": " << h.at(i) << std::endl;
        std::cout << "T " << i << ": " << T.at(i) << std::endl;
    }
    */

    
    int width = (int) std::round(dims[0] / dims[2]) + 1;
    int height = (int) std::round(dims[1] / dims[3]) + 1;
    // std::cout << xLength << " " << Dx << " " << xLength / Dx << " " << std::round(xLength / Dx) << std::endl;
    std::set<int> exclude;
    float *array = (float *) malloc(width * height * sizeof(float));
    for(int i = 0; i < width * height; i++) {
        array[i] = 0;
    }
    /*
    std::cout << "w: " << width << std::endl;
    std::cout << "h: " << height << std::endl;
    for(int i = 0; i < dims.size(); i++) {
        std::cout << "h " << i << ": " << boundaries[i].h << std::endl;
        std::cout << "T " << i << ": " << boundaries[i].temperature << std::endl;
    }
    */

    for(int i = 0; i < 2 * N; i++) {
        if(h[i] == 0.0f && T[i] != 0.0f) {
            if(i < 2) {
                int offset = 0;
                if(i == 1) {
                    offset = width * height - width;
                }
                for(int j = 0; j < width; j++) {
                    array[j + offset] = T[i];
                    exclude.insert(j + offset);
                }
            } else {
                int offset = 0;
                if(i == 3) {
                    offset = width - 1;
                }
                for(int j = 0; j < height; j++) {
                    array[j * width + offset] = T[i];
                    exclude.insert(j * width + offset);
                }
            }
        }
    }
    /*
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            std::cout << array[i * width + j] << " ";
        }
        std::cout << std::endl;
    }
    */
    /*
    for(int i = 0; i < height; i++) {
        array[i * width] = 70.491667;
        exclude.insert(i * width);
    }
    */

    Matrix *m = new Matrix(array, height, width);

    // m->Display();
    
    SystemND *system = new SystemND(m, boundaries, k, N);
    system->Dx = dims[2];
    system->Dy = dims[3];

    Matrix *solution = Solve(*system, exclude)->distro;
    // solution->Display();
    std::vector<float> result;
    for(int i = 0; i < height * width; i++) {
        result.push_back(solution->get(i / width, i % width));
    }
    return result;
}



int main() {
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
    float xLength = 600; // 0.284988;
    float yLength = 200; // M_PI * .0127;
    float Dx = 20;
    float Dy = 100; // M_PI * .0127;
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
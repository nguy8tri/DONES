#include "matrix.hpp"

#include <cassert>
#include <iostream>

float* Vector::GetVector() {
    return vector;
}

float Matrix::get(int r, int c) const {
        return matrix[r * width + c];
    }

Vector Vector::Copy() const {
    float* arr = new float[sizeof(vector)];
        for(int i = 0; i < sizeof(arr); i++) {
            arr[i] = vector[i];
        }
        return Vector(arr);
}

Vector Matrix::GaussianSolve(Vector v) const {
    if(height != width) {
        throw "Error - No unique solution";
    }
    float* solution = new float[height * width];
    int s = 0;
    float* copyM = Copy().matrix;
    float* copyV = v.Copy().GetVector();
    for(int j = 0; j < width; j++) {
        for(int i = j + 1; i < height; i++) {
            int mult = copyM[i * width + j] / copyM[j * width + j];
            for(int k = j + 1; k < width; k++) {
                copyM[i * width + k] -= mult * copyM[j * width + k];
            }
            copyV[i] -= mult * copyV[j];
        }
    }
    for(int j = height - 1; j >= 0; j--) {
        int sum = 0;
        int i;
        for(i = width - 1; i > j; i--) {
            sum += copyV[i] * copyM[i * width + j];
        }
        copyV[i] = (copyV[i] - sum) / copyM[i * width + j];
    }
    return copyV;
}

Matrix Matrix::Copy() const {
    float* arr = new float[height * width];
        for(int i = 0; i < height * width; i++) {
            arr[i] = matrix[i];
        }
        return Matrix(arr, height, width);
}

void Matrix::Display() const {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            std::cout << matrix[i * width + j] << " ";
        }
        std::cout << std::endl;
    }
}


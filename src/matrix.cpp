#include "matrix.hpp"

#include <cassert>
#include <iostream>

Vector::~Vector() {}

Matrix::~Matrix() {}

float* Vector::GetVector() {
    return vector;
}

float Matrix::get(int r, int c) const {
        return matrix[r * width + c];
    }

Vector Vector::Copy() const {
    float* arr = new float[sizeof(vector)];
        for(int i = 0; i < length; i++) {
            arr[i] = vector[i];
        }
    return Vector(arr, length);
}

Vector Matrix::GaussianSolve(Vector v) const {
    if(height != width) {
        throw "Error - No unique solution";
    }
    // v.Display();
    float *b = v.vector;
    for(int j = 0; j < width; j++) {
        for(int i = j + 1; i < height; i++) {
            float mult = matrix[i * width + j] / matrix[j * width + j];
            // std::cout << matrix[i * width + j] << " " << matrix[j * width + j] << std::endl;
            for(int k = j + 1; k < width; k++) {
                matrix[i * width + k] -= mult * matrix[j * width + k];
            }
            b[i] -= mult * b[j];
        }
    }
    // Display();
    // v.Display();
    for(int j = height - 1; j >= 0; j--) {
        float sum = 0;
        int i;
        for(i = width - 1; i > j; i--) {
            sum += b[i] * matrix[j * width + i];
            // std::cout << b[i] << " " << matrix[j * width + i] << std::endl;
        }
        // std::cout << "b: " << b[j] << " " << sum << " " << matrix[j * width + i] << std::endl;
        b[j] = (b[j] - sum) / matrix[j * width + i];
        // std::cout << std::endl;
    }
    return *(new Vector(b, v.length));
}



Matrix Matrix::Copy() const {
    float* arr = new float[height * width];
        for(int i = 0; i < height * width; i++) {
            arr[i] = matrix[i];
        }
    return Matrix(arr, height, width);
}

void Matrix::Display() const {
    // std::cout << height << " " << width << std::endl;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            printf("%-8.4f ", matrix[i * width + j]);
        }
        std::cout << std::endl;
    }
}

void Vector::Display() {
    for(int i = 0; i < length; i++) {
        std::cout << vector[i] << std::endl;
    }
    std::cout << std::endl;
}

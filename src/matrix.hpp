#ifndef MATRIX_H
#define MATRIX_H


class Vector {
public:
    ~Vector();
    Vector();
    Vector(float* arr, int size) : vector(arr), length(size) {};
    float* GetVector();
    Vector Copy() const;
    void Display();
    float* vector;
    int length;
};

class Matrix {
public:
    ~Matrix();
    Matrix();
    Matrix(float* arr, int r, int c) : matrix(arr), height(r), width(c) {};
    Matrix(Vector* arr, int r, int c) : matrix(arr->GetVector()), height(r), width(c) {};
    Vector GaussianSolve(Vector v) const;
    void Load(float arr[]);
    void Display() const;
    Matrix Copy() const;
    float get(int r, int c) const;
    int Height() {
        return height;
    }
    int Width() {
        return width;
    }
    const float* getMatrix() {
        return matrix;
    }
private:
    float* matrix;
    int height;
    int width;
};




#endif
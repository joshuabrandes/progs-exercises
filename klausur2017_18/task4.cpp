//
// Created by Joshua Brandes on 10.07.24.
//

#include <iostream>

class Vector {
public:
    explicit Vector(int numElem) : numElem_(numElem) {
        elem_ = new float[numElem_];
    }

    // fixes warning of deallocating a pointer when returning from function with a copy of the object
    Vector(const Vector &vec) : numElem_(vec.numElem_) {
        elem_ = new float[numElem_];
        for (int i = 0; i < numElem_; i++) {
            elem_[i] = vec.elem_[i];
        }
    }

    ~Vector() {
        delete[] elem_;
    }

    float &operator[](int i) {
        return elem_[i];
    }

private:
    int numElem_;
    float *elem_;
};

Vector cross(Vector x, Vector y) {
    Vector result(3);
    result[0] = x[1] * y[2] - x[2] * y[1];
    result[1] = x[2] * y[0] - x[0] * y[2];
    result[2] = x[0] * y[1] - x[1] * y[0];

    return result;
}

void printVector(Vector vec) {
    std::cout << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")" << std::endl;
}

int main() {
    Vector a(3);
    Vector b(3);

    a[0] = 1;
    a[1] = 0;
    a[2] = 0;
    b[0] = 0;
    b[1] = 1;
    b[2] = 0;

    Vector c = cross(a, b);
    printVector(c);

    return 0;
}

#include <cstdint>
#include <iostream>

template<typename T>
class Image3D {
public:
    Image3D(uint16_t xd, uint16_t yd, uint16_t zd);

    ~Image3D();

    T at(uint16_t x, uint16_t y, uint16_t z);

    void insert(T value, uint16_t x, uint16_t y, uint16_t z);
    /* Weitere Deklarationen */

private:
    // T ***data;

    /* Weitere Deklarationen */
};

template<>
class Image3D<double> {
public:
    Image3D(uint16_t xd, uint16_t yd, uint16_t zd) {
        this->xd = xd;
        this->yd = yd;
        this->zd = zd;
        data = new double[xd * yd * zd];
        std::cout << "Image constructed." << std::endl;
    }

    ~Image3D() {
        delete[] data;
        std::cout << "Image deleted." << std::endl;
    }

    // copy constructor
    Image3D(const Image3D &other)
            : xd(other.xd), yd(other.yd), zd(other.zd) {
        data = new double[xd * yd * zd];
        std::copy(other.data, other.data + (xd * yd * zd), data);
        std::cout << "Image copy constructed." << std::endl;
    }

    // copy assign operator
    Image3D &operator=(const Image3D &other) {
        if (this != &other) {
            delete[] data;
            xd = other.xd;
            yd = other.yd;
            zd = other.zd;
            data = new double[xd * yd * zd];
            std::copy(other.data, other.data + (xd * yd * zd), data);
        }
        std::cout << "Image copy assigned." << std::endl;
        return *this;
    }

    double at(uint16_t x, uint16_t y, uint16_t z) {
        return data[calculate_index(x, y, z)];
    }

    void insert(double value, uint16_t x, uint16_t y, uint16_t z) {
        data[calculate_index(x, y, z)] = value;
    }

private:
    double *data;
    uint16_t xd, yd, zd;

    int calculate_index(uint16_t x, uint16_t y, uint16_t z) const {
        return (z * xd * xd) + (y * xd) + x;
    }
};

template<>
class Image3D<int> {
public:
    Image3D(uint16_t xd, uint16_t yd, uint16_t zd) {
        data = new int **[xd];
        for (uint16_t i = 0; i < xd; i++) {
            data[i] = new int *[yd];
            for (uint16_t j = 0; j < yd; ++j) {
                data[i][j] = new int[zd];
            }
        }
        std::cout << "Int image constructed." << std::endl;
    }

    ~Image3D() {
        for (uint16_t i = 0; data[i] != nullptr; ++i) { // effizienter als i++, wird aber nach Schleife erst ausgeführt
            for (int j = 0; data[i][j] != nullptr; ++j) {
                delete[] data[i][j];
            }
            delete[] data[i];
        }

        delete[] data;
        std::cout << "Int image deleted." << std::endl;
    }

    // copy constructor
    Image3D(const Image3D &other) {
        uint16_t xd = 0;
        while (other.data[xd] != nullptr) ++xd;

        data = new int **[xd + 1];  // +1 für den nullptr-Terminator
        for (uint16_t i = 0; i < xd; ++i) {
            uint16_t yd = 0;
            while (other.data[i][yd] != nullptr) ++yd;

            data[i] = new int *[yd + 1];  // +1 für den nullptr-Terminator
            for (uint16_t j = 0; j < yd; ++j) {
                uint16_t zd = 0;
                while (other.data[i][j][zd] != 0) ++zd;  // Annahme: 0 als Terminator

                data[i][j] = new int[zd + 1];  // +1 für den Terminator
                for (uint16_t k = 0; k < zd; ++k) {
                    data[i][j][k] = other.data[i][j][k];
                }
                data[i][j][zd] = 0;  // Terminator
            }
            data[i][yd] = nullptr;  // Terminator
        }
        data[xd] = nullptr;  // Terminator
        std::cout << "Image copy constructed." << std::endl;
    }

    // copy assign operator
    Image3D &operator=(const Image3D &other) {
        if (this != &other) {
            this->~Image3D();
            new(this) Image3D(other);  // Placement new
        }
        std::cout << "Image copy assigned." << std::endl;
        return *this;
    }

    int at(uint16_t x, uint16_t y, uint16_t z) const {
        return data[x][y][z];
    }

    void insert(int value, uint16_t x, uint16_t y, uint16_t z) {
        data[x][y][z] = value;
    }

private:
    int ***data;
};

int main() {
    Image3D<double> *image3D = new Image3D<double>(4, 2, 3);

    auto img_double = image3D;

    image3D->insert(5.0, 0, 0, 0);
    auto val = img_double->at(0, 0, 0);
    std::cout << "Double value from copy: " << val << std::endl;

    auto *image_double_copy = new Image3D<double>(*image3D);
    std::cout << "Value from constructed copy: " << image_double_copy->at(0, 0, 0) << std::endl;

    delete image3D;
    delete img_double;
    delete image_double_copy;

    auto *int_image = new Image3D<int>(4, 2, 3);
    int_image->insert(5, 0, 0, 0);
    auto val_int = int_image->at(0, 0, 0);
    std::cout << "Int value: " << val_int << std::endl;

    delete int_image;
}

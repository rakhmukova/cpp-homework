#include "operations.h"

template<typename T>
T Square(T a) {
    return a * a;
}

template<typename T>
T Sum(T a, T b) {
    return a + b;
}

template<typename T>
Matrix<T> Transpose(const Matrix<T>& a) {
    size_t row = a.size();
    size_t column = a[0].size();
    Matrix<T> transposed(column, std::vector<int>(row));
    for (unsigned int i = 0; i < row; ++i) {
        for (unsigned int j = 0; j < column; ++j) {
            transposed[j][i] = a[i][j];
        }
    }

    return transposed;
}

template<typename T>
Matrix<T> MultiplySquare(const Matrix<T>& a, const Matrix<T>& b) {
    int dim = a.size();
    Matrix<T> transposed(dim, std::vector<int>(dim));
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            for (int k = 0; k < dim; ++k) {
                transposed[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return transposed;
}

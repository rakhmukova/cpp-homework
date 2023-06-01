#pragma once

#include <vector>

template<typename T>
using Matrix = std::vector<std::vector<T>>;

template<typename T>
T Square(T a);

template<typename T>
T Sum(T a, T b);

template<typename T>
Matrix<T> Transpose(const Matrix<T>& a);

template<typename T>
Matrix<T> MultiplySquare(const Matrix<T>& a, const Matrix<T>& b);

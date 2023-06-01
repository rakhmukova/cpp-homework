#include <gtest/gtest.h>

#include <random>

#include <iostream>

#include "map_reduce.cpp"
#include "operations.cpp"
// fix imports

int generateRandomInt(int min, int max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

Matrix<int> generateRandomMatrix(size_t dim, int min, int max) {
    Matrix<int> matrix(dim, std::vector<int>(dim));
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            matrix[i][j] = generateRandomInt(min, max);
        }
    }

    return matrix;
}

template<typename InputT, typename OutputT>
void compareResults(const std::vector<InputT>& input,
                    const std::function<OutputT(InputT)>& map_func,
                    const std::function<OutputT(OutputT, OutputT)>& reduce_func,
                    const OutputT& neutral_element) {
    auto start = std::chrono::system_clock::now();
    auto sequential_result = sequentialMapReduce(input, map_func, reduce_func, neutral_element);
    auto end = std::chrono::system_clock::now();
    auto sequential_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "\tSequential MapReduce: " << sequential_duration << " ms\n";

    start = std::chrono::system_clock::now();
    auto openmp_result = openmpMapReduce(input, map_func, reduce_func, neutral_element);
    end = std::chrono::system_clock::now();
    auto openmp_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "\tOpenMP MapReduce: " << openmp_duration << " ms\n";

    ASSERT_EQ(sequential_result, openmp_result);
}

TEST(MapReduce, Empty) {
    std::vector<int> input;
    std::function<int(int)> square_func = Square<int>;
    std::function<int(int, int)> sum_func = Sum<int>;
    int neutral_element = 0;

    int sequential_result = sequentialMapReduce(input, square_func, sum_func, neutral_element);
    int openmp_result = openmpMapReduce(input, square_func, sum_func, neutral_element);

    ASSERT_EQ(sequential_result, openmp_result);
}

TEST(MapReduce, SquareSum) {
    std::function<int(int)> square_func = Square<int>;
    std::function<int(int, int)> sum_func = Sum<int>;
    int neutral_element = 0;

    for (int i = 1000; i <= 10000000; i *= 10) {
        std::cout << "\nNumber of elements: " << i << '\n';
        std::vector<int> input(i);
        for (int j = 0; j < i; ++j) {
            input[j] = generateRandomInt(0, 10);
        }

        compareResults(input, square_func, sum_func, neutral_element);
    }
}

TEST(MapReduce, TransposeMultiply) {
    std::function<Matrix<int>(Matrix<int>)> transpose_func = Transpose<int>;
    std::function<Matrix<int>(Matrix<int>, Matrix<int>)> multiply_func = MultiplySquare<int>;
    Matrix<int> neutral_element = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    for (int i = 10; i <= 100000; i *= 10) {
        std::cout << "\nNumber of elements: " << i << '\n';
        std::vector<Matrix<int>> input(i);
        for (int j = 0; j < i; ++j) {
            input[j] = generateRandomMatrix(3, 0, 2);
        }

        compareResults(input, transpose_func, multiply_func, neutral_element);
    }
}

#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>
#include <iostream>
#include <algorithm>

template<typename T>
bool comp_with_pair(const std::pair<T, T>& a, const std::pair<T, T>& b);

template<typename T>
struct Matrix {
public:
    Matrix() {
        rows_ = cols_ = NULL;
        num_of_rows_ = num_of_cols_ = length_ = 0;
    }

    Matrix(const Matrix<T>& __base__);

    Matrix(const std::vector<std::vector<T>>& __vbase__);

    ~Matrix() {
        for (size_t i = 0; i < num_of_rows_; ++i) {
            if (rows_[i])   delete[] rows_[i];
            rows_[i] = NULL;
        }
        delete[] rows_;
        cols_ = rows_ = NULL;
    }

    void PrintMatrix() {
        for (size_t i = 0; i < num_of_rows_; ++i) {
            for (size_t j = 0; j < num_of_cols_; ++j) {
                std::cout << rows_[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

    const std::pair<size_t, size_t> size() const {
        return std::make_pair(num_of_rows_, num_of_cols_);
    }

    Matrix<T> operator+(const Matrix<T>& _factor_);

    Matrix<T> operator*(const Matrix<T>& _factor_);

    /**
     * @brief Get column. TODO - modify this function to use pointers
     * 
     * @param idx 
     * @return std::vector<T> 
     */
    std::vector<T> operator[](unsigned int idx) const;

    template<typename U>
    friend Matrix<U> operator+(const std::vector<std::vector<U>>& _first_, const Matrix<U>& _second_);

    template<typename U>
    friend Matrix<U> operator*(const U& _scale_, const Matrix<U>& _mat_);

private:
    T** rows_;
    T** cols_;  // TODO - initialize with rows together
    size_t num_of_rows_, num_of_cols_;
    size_t length_;
};


template<typename T>
T operator*(const std::vector<T>& a, const std::vector<T>& b);


#endif // MATRIX_H_INCLUDED
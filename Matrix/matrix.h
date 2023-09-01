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
        rows_ = NULL;
        num_of_rows_ = num_of_cols_ = length_ = 0;
    }

    Matrix(const Matrix<T>& __base__);

    Matrix(const std::vector<std::vector<T>>& __vbase__);

    template<typename U>
    friend struct Matrix;

    template<typename U>
    Matrix(const Matrix<U>& __ubase__) :
            num_of_rows_(__ubase__.num_of_rows_),
            num_of_cols_(__ubase__.num_of_cols_),
            length_(__ubase__.length_) {
        rows_ = new T*[num_of_rows_];
        for (size_t i = 0; i < num_of_rows_; ++i) {
            rows_[i] = new T[num_of_cols_];
            for (size_t j = 0; j < num_of_cols_; ++j) {
                rows_[i][j] = static_cast<T>(__ubase__.rows_[i][j]);
            }
        }
    }

    ~Matrix() {
        if (rows_) {
            for (size_t i = 0; i < num_of_rows_; ++i) {
                if (rows_[i])   delete[] rows_[i];
                rows_[i] = NULL;
            }
            delete[] rows_;
        }
        rows_ = NULL;
        num_of_cols_ = num_of_rows_ = length_ = 0;
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

    /**
     * @brief Transpose
     * 
     * @return Matrix<T> transposed new matrix
     */
    Matrix<T> Transpose() const;

    Matrix<T> operator-() const;

    Matrix<T> operator+() const { return *this; }

    Matrix<T> operator+(const Matrix<T>& _factor_);

    Matrix<T> operator-(const Matrix<T>& _factor_);

    Matrix<T> operator*(const Matrix<T>& _factor_);

    Matrix<T> operator*(const T& _scale_);

    Matrix<T>& operator=(const Matrix<T>& _mat_) {
        if (rows_) {
            for (size_t i = 0; i < num_of_rows_; ++i) {
                if (rows_[i])   delete[] rows_[i];
            }
        }
        num_of_rows_ = _mat_.num_of_rows_;
        num_of_cols_ = _mat_.num_of_cols_;
        rows_ = new T*[num_of_rows_];
        for (size_t i = 0; i < num_of_rows_; ++i) {
            rows_[i] = new T[num_of_cols_];
            for (size_t j = 0; j < num_of_cols_; ++j) {
                rows_[i][j] = _mat_.rows_[i][j];
            }
        }

        return *this;
    }

    /**
     * @brief Get row. TODO - modify this function to use pointers
     * 
     * @param idx 
     * @return std::vector<T> 
     */
    std::vector<T> operator[](unsigned int idx) const;

    /**
     * @brief Get col
     * 
     * @param idx 
     * @return std::vector<T> 
     */
    std::vector<T> col(unsigned int idx) const;

    template<typename U>
    friend Matrix<U> operator+(const std::vector<std::vector<U>>& _first_, const Matrix<U>& _second_);

    template<typename U>
    friend Matrix<U> operator*(const U& _scale_, const Matrix<U>& _mat_);

    // template<typename U>
    // friend Matrix<U> operator*(const U& _scale_, const Matrix<T>& _mat_);
    // friend typename std::enable_if<!std::is_same<U, T>::value, Matrix<U>>::type operator*(const U& _scale_, const Matrix<T>& _mat_);

private:
    T** rows_;
    size_t num_of_rows_, num_of_cols_;
    size_t length_;
};


template<typename T>
T operator*(const std::vector<T>& a, const std::vector<T>& b);


#endif // MATRIX_H_INCLUDED

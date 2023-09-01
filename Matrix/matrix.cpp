#include "matrix.h"
#include <assert.h>

using namespace std;

template struct Matrix<int>;
template struct Matrix<int64_t>;
template struct Matrix<double>;
template struct Matrix<float>;


template<typename T>
bool comp_with_pair(const std::pair<T, T>& a, const std::pair<T, T>& b) {
    return a.first == b.first && a.second == b.second;
}

template<typename T>
T operator*(const std::vector<T>& a, const std::vector<T>& b) {
    assert(a.size() == b.size());
    T res = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        res += a[i] * b[i];
    }
    return res;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& __base__)
    : num_of_rows_(__base__.num_of_rows_),
      num_of_cols_(__base__.num_of_cols_),
      length_(__base__.length_) {
    rows_ = new T*[num_of_rows_];
    for (size_t i = 0; i < num_of_rows_; ++i) {
        rows_[i] = new T[num_of_cols_];
        for (size_t j = 0; j < num_of_cols_; ++j) {
            rows_[i][j] = __base__.rows_[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& __vbase__) {
    num_of_rows_ = __vbase__.size();
    num_of_cols_ = __vbase__[0].size();

    rows_ = new T*[num_of_rows_];

    for (size_t i = 0; i < num_of_rows_; ++i) {
        rows_[i] = new T[num_of_cols_];
        std::copy(__vbase__[i].begin(), __vbase__[i].end(), rows_[i]);
    }
}


template<typename T>
Matrix<T> Matrix<T>::Transpose() const {
    std::vector<std::vector<T>> cols;
    for (size_t i = 0; i < num_of_cols_; ++i) {
        std::vector<T> col = (*this)[i];
        cols.push_back(col);
    }
    return Matrix<T>(cols);
}

template<typename T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix<T> res(*this);
    for (size_t i = 0; i < num_of_rows_; ++i) {
        for (size_t j = 0; j < num_of_cols_; ++j) {
            res.rows_[i][j] *= -1;
        }
    }
    return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& _factor_) {
    return *this + (-_factor_);
}

template<typename T>
std::vector<T> Matrix<T>::operator[](unsigned int idx) const {
    assert(idx < num_of_rows_);
    return std::vector<T>(rows_[idx], rows_[idx] + num_of_cols_);
}

template<typename T>
std::vector<T> Matrix<T>::col(unsigned int idx) const {
    assert(idx < num_of_cols_);
    std::vector<T> colmun;
    for (size_t i = 0; i < num_of_rows_; ++i) {
        colmun.push_back(rows_[i][idx]);
    }
    return colmun;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& _factor_) {
    assert(num_of_rows_ == _factor_.num_of_rows_ && num_of_cols_ == _factor_.num_of_cols_);

    Matrix<T> res(*this);
    for (size_t i = 0; i < num_of_rows_; ++i) {
        for (size_t j = 0; j < num_of_cols_; ++j) {
            res.rows_[i][j] += _factor_.rows_[i][j];
        }
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& _factor_) {
    const size_t &r = _factor_.num_of_rows_;
    const size_t &c = _factor_.num_of_cols_;
    assert(this->num_of_rows_ == c && this->num_of_cols_ == r);

    std::vector<std::vector<T>> res;
    for (size_t i = 0; i < this->num_of_rows_; ++i) {
        std::vector<T> new_row;
        for (size_t j = 0; j < c; ++j) {
            T value = (*this)[i] * _factor_.col(j);
            new_row.push_back(value);
        }
        res.push_back(new_row);
    }
    return Matrix<T>(res);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T& _scale_) {
    for (size_t i = 0; i < num_of_rows_; ++i) {
        for (size_t j = 0; j < num_of_cols_; ++j) {
            rows_[i][j] *= _scale_;
        }
    }
    return Matrix<T>(*this);
}

template<typename T>
Matrix<T> operator+(const vector<vector<T>>& _first_, const Matrix<T>& _second_) {
    const size_t &r = _second_.num_of_rows_, &c = _second_.num_of_cols_;
    assert(_first_.size() == r &&
        _first_[0].size() == c);

    std::vector<std::vector<T>> res;
    for (size_t i = 0; i < r; ++i) {
        std::vector<T> res_row;
        for (size_t j = 0; j < c; ++j) {
            res_row.push_back(_second_.rows_[i][j] + _first_[i][j]);
        }
        res.push_back(res_row);
    }
    return Matrix<T>(res);
}

template<typename T>
Matrix<T> operator*(const T& _scale_, const Matrix<T>& _mat_) {
    Matrix<T> result(_mat_);
    for (size_t i = 0; i < result.num_of_rows_; ++i) {
        for (size_t j = 0; j < result.num_of_cols_; ++j) {
            result.rows_[i][j] *= _scale_;
        }
    }
    return result;
}

template Matrix<int> operator*<int>(const int& _scale_, const Matrix<int>& _mat_);
template Matrix<double> operator*<double>(const double& _scale_, const Matrix<double>& _mat_);
// template Matrix<double> operator*<double>(const double& _scale_, const Matrix<int>& _mat_);
// template Matrix<double> operator*<double>(const int& _scale_, const Matrix<double>& _mat_);

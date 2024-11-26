#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include "common.hpp"

namespace seismath {

template <typename T>
vec2d<T> mult2DMat(const vec2d<T>& A, const vec2d<T>& B) {
    size_t rows = A.size();
    size_t cols = A[0].size();
    vec2d<T> result(rows, vec1d<T>(cols, 0.0f));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = A[i][j] * B[i][j];
        }
    }
    return result;
}

template <typename T>
vec2d<T> scalar2DMat(T value, const vec2d<T>& A) {
    size_t rows = A.size();
    size_t cols = A[0].size();
    vec2d<T> result(rows, vec1d<T>(cols, 0.0f));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = value * A[i][j];
        }
    }
    return result;
}

template <typename T>
vec2d<T> add2DMat(const vec2d<T>& A, const vec2d<T>& B) {
    size_t rows = A.size();
    size_t cols = A[0].size();
    vec2d<T> result(rows, vec1d<T>(cols, 0.0f));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

template <typename T>
vec2d<T> sub2DMat(const vec2d<T>& A, const vec2d<T>& B) {
    size_t rows = A.size();
    size_t cols = A[0].size();
    vec2d<T> result(rows, vec1d<T>(cols, 0.0f));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

template <typename T>
vec1d<T> mult1DVec(const vec1d<T>& A, const vec1d<T>& B) {

    size_t size = A.size();
    vec1d<T> result(size, 0.0f);

    for (size_t i = 0; i < size; ++i) {
        result[i] = A[i] * B[i];
    }
    return result;
}

template <typename T>
vec1d<T> scalar1DVec(T value, const vec1d<T>& A) {
    size_t size = A.size();
    vec1d<T> result(size, 0.0f);

    for (size_t i = 0; i < size; ++i) {
        result[i] = value * A[i];
    }
    return result;
}

template <typename T>
vec1d<T> add1DVec(const vec1d<T>& A, const vec1d<T>& B) {
    if (A.size() != B.size()) {
        throw std::invalid_argument("Vectors must have the same size for addition.");
    }

    size_t size = A.size();
    vec1d<T> result(size, 0.0f);

    for (size_t i = 0; i < size; ++i) {
        result[i] = A[i] + B[i];
    }
    return result;
}

template <typename T>
vec1d<T> sub1DVec(const vec1d<T>& A, const vec1d<T>& B) {

    size_t size = A.size();
    vec1d<T> result(size, 0.0f);

    for (size_t i = 0; i < size; ++i) {
        result[i] = A[i] - B[i];
    }
    return result;
}
}

#endif // !MATRIX_HPP

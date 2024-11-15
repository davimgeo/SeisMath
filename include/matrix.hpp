#pragma once

#include "imports.hpp"
#include "common.hpp"

// Multiply two matrices
template <typename T>
vec2d<T> multMat(const vec2d<T>& A, const vec2d<T>& B) {
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

// Multiply matrix by a scalar
template <typename T>
vec2d<T> scalarMat(T value, const vec2d<T>& A) {
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

// Add two matrices
template <typename T>
vec2d<T> addMat(const vec2d<T>& A, const vec2d<T>& B) {
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

// Subtract two matrices
template <typename T>
vec2d<T> subMat(const vec2d<T>& A, const vec2d<T>& B) {
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


#include "../include/common.hpp"
#include "../include/imports.hpp"

template <typename T>
vec2d<T> mulMat(const vec2d<T>& A, const vec2d<T>& B) {
    size_t height = A.size();
    size_t width = A[0].size();

    if (B.size() != height || B[0].size() != width) {
        throw std::invalid_argument("Matrix dimensions do not match");
    }

    vec2d<T> result(height, vec1d<T>(width, T()));

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            result[i][j] = A[i][j] * B[i][j];
        }
    }

    return result;
}

template <typename T>
vec2d<T> scalarMat(const vec2d<T>& A, T value) {

    vec2d<T> result(A.size(), vec1d<T>(A[0].size(), T()));

    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < A[i].size(); j++) {
            result[i][j] = A[i][j] * value;
        }
    }

    return result;
}

template <typename T>
vec2d<T> addMat(const vec2d<T>& A, const vec2d<T>& B) {
    size_t height = A.size();
    size_t width = A[0].size();

    if (B.size() != height || B[0].size() != width) {
        throw std::invalid_argument("Matrix dimensions do not match");

    vec2d<T> result(height, vec1d<T>(width, T()));

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    return result;
}


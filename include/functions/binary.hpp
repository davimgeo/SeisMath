#ifndef BINARY_HPP
#define BINARY_HPP

#include <fstream>
#include <stdexcept>
#include <string>
#include "common.hpp"

namespace seismath {

template <typename T>
void write1dVec(const vec1d<T> &vec, const std::string &PATH) {
    std::ofstream fout(PATH, std::ios::out | std::ios::binary); 

    if (!fout.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }

    for (const auto& elem : vec) {
        fout.write(reinterpret_cast<const char*>(&elem), sizeof(T));
        }

    fout.close(); 
}

template <typename T>
void write2dVec(const vec2d<T>& vec, const std::string& PATH, const char order) {
    std::ofstream fout(PATH, std::ios::out | std::ios::binary); 

    if (!fout.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }

    size_t rows = vec.size();
    size_t cols = vec[0].size();

    for (const auto& row : vec) {
        for (const auto& val : row) {
            fout.write(reinterpret_cast<const char*>(&val), sizeof(T));
        }
    }

    fout.close(); 
}

template <typename T>
void write1dVecAs2d(const std::vector<T>& vec, const size_t rows, const size_t cols, const std::string& PATH, const char order) {
    std::ofstream fout(PATH, std::ios::out | std::ios::binary);

    if (!fout.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            fout.write(reinterpret_cast<const char*>(&vec[i * cols + j]), sizeof(T));
        }
    }

    fout.close();
}

template <typename T>
vec2d<T> load2dVec(const size_t rows, const size_t cols, const std::string& PATH, const char order) {
    std::fstream fin;
    fin.open(PATH, std::ios::in | std::ios::binary);

    if (!fin.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }

    vec2d<T> result(rows, std::vector<T>(cols));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            fin.read(reinterpret_cast<char*>(&result[i][j]), sizeof(T));
        }
    }

    fin.close();
    return result;
}

template <typename T>
std::vector<T> loadFlattened2dVec(size_t rows, size_t cols, const std::string& PATH, char order) {
    std::fstream fin;
    fin.open(PATH, std::ios::in | std::ios::binary);

    if (!fin.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }

    std::vector<T> result(rows * cols);

    for (size_t i = 0; i < rows * cols; i++) {
        fin.read(reinterpret_cast<char*>(&result[i]), sizeof(T));
    }

    fin.close();
    return result;
}
}

#endif // !BINARY_HPP

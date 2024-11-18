#pragma once

#include <fstream>
#include <stdexcept>
#include "common.hpp"

template <typename T>
void write2dvec(const vec2d<T> &vec) {
    std::ofstream fout("file.bin", std::ios::out | std::ios::binary); 

    if (!fout.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }

    size_t rows = vec.size();
    size_t cols = vec[0].size();

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            fout.write(reinterpret_cast<const char*>(&vec[i][j]), sizeof(vec[i][j]));
        }
    }

    fout.close(); 
}

template <typename T>
void write1dVecAs2d() {

}


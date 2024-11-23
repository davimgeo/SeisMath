#ifndef UTILS_HPP
#define UTILS_HPP

#include "SeisMath.hpp"
#include <utility>

namespace seismath {

    template <typename T>
    void print1D(const vec1d<T>& vec) {
        std::cout << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i];
            if (i != vec.size() - 1) { 
                std::cout << ", ";
            }
        }
        std::cout << "]" << '\n';
    }

    template <typename T>
    void print2D(const vec2d<T>& vec) {
        std::cout << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            const auto& row = vec[i];
            std::cout << "[";
            for (size_t j = 0; j < row.size(); ++j) {
                std::cout << row[j];
                if (j != row.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "]";
            if (i != vec.size() - 1) {
                std::cout << ",\n ";
            }
        }
        std::cout << "]" << std::endl;
    }
    
    template <typename T>
    void printPlot1D(const vec1d<T>& vec) {
        for (const auto& elem : vec) {
            std::cout << elem << '\n';
        }
    }

    template <typename T>
    void printPlot2D(const vec2d<T>& vec) {
        for (size_t i = 0; i < vec.size(); ++i) {
            for (size_t j = 0; j < vec[0].size(); ++j) {
                    std::cout << vec[i][j] << '\n';
                }
            }
        }
}
#endif // UTILS_HPP

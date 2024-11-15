#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "include/imports.hpp"
#include "include/common.hpp"
#include "include/matrix.hpp"
#include "include/FD.hpp"
#include "include/wavelet.hpp"

// Function to export 2D matrix to a binary file
template <typename T>
void exportBinaryFile(const vec2d<T>& matrix, const std::string& file_path) {
    std::ofstream outfile(file_path, std::ios::binary);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }

    // Write matrix dimensions
    uint32_t rows = static_cast<uint32_t>(matrix.size());
    uint32_t cols = static_cast<uint32_t>(matrix[0].size());
    outfile.write(reinterpret_cast<const char*>(&rows), sizeof(uint32_t));
    outfile.write(reinterpret_cast<const char*>(&cols), sizeof(uint32_t));

    // Write matrix data
    for (const auto& row : matrix) {
        outfile.write(reinterpret_cast<const char*>(row.data()), row.size() * sizeof(T));
    }

    outfile.close();
}

// Function to load 2D matrix from a binary file
template <typename T>
vec2d<T> loadBinaryFile(const std::string& file_path) {
    std::ifstream infile(file_path, std::ios::binary);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }

    // Read matrix dimensions
    uint32_t rows, cols;
    infile.read(reinterpret_cast<char*>(&rows), sizeof(uint32_t));
    infile.read(reinterpret_cast<char*>(&cols), sizeof(uint32_t));

    // Read matrix data
    vec2d<T> matrix(rows, vec1d<T>(cols, 0.0f));
    for (auto& row : matrix) {
        infile.read(reinterpret_cast<char*>(row.data()), cols * sizeof(T));
    }

    infile.close();
    return matrix;
}

int main() {
    // Define simulation parameters
    uint16_t Nx = 416, Nz = 160, Nt = 5001;
    float dx = 10.0f, dz = 10.0f, dt = 4.0e-4;
    int pos0 = 50, posf = 50;
    float fmax = 10.0f;

    // Initialize the source wavelet (property)
    vec1d<float> property = generateRicker(Nt, dt, fmax);

    // Initialize the model (velocity squared matrix)
    vec2d<float> model(Nz, vec1d<float>(Nx, 2500.0f)); // Example constant velocity

    vec2d<float> result = compute_2D(property, Nx, Nz, Nt, dx, dz, dt, pos0, posf, model);

    // Export the result to a binary file
    std::string output_file = "wavefield_result.bin";
    exportBinaryFile(result, output_file);
    std::cout << "Wavefield result saved to " << output_file << std::endl;

    // Load the result back for verification
    vec2d<float> loaded_result = loadBinaryFile<float>(output_file);
    std::cout << "Loaded wavefield dimensions: " << loaded_result.size() << "x" << loaded_result[0].size() << std::endl;

    return 0;
}


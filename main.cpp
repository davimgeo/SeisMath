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
void exportBinaryFile1D(const vec1d<T>& array, size_t Nx_ext, size_t Nz_ext, const std::string& file_path) {
    std::ofstream outfile(file_path, std::ios::binary);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }

    // Write array dimensions
    uint32_t rows = static_cast<uint32_t>(Nz_ext);
    uint32_t cols = static_cast<uint32_t>(Nx_ext);
    outfile.write(reinterpret_cast<const char*>(&rows), sizeof(uint32_t));
    outfile.write(reinterpret_cast<const char*>(&cols), sizeof(uint32_t));

    // Write array data
    outfile.write(reinterpret_cast<const char*>(array.data()), array.size() * sizeof(T));

    outfile.close();
}

// Função para carregar array unidimensional de um arquivo binário
template <typename T>
vec1d<T> loadBinaryFile1D(const std::string& file_path, size_t& Nx_ext, size_t& Nz_ext) {
    std::ifstream infile(file_path, std::ios::binary);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file. Please verify the file path.");
    }

    // Read array dimensions
    uint32_t rows, cols;
    infile.read(reinterpret_cast<char*>(&rows), sizeof(uint32_t));
    infile.read(reinterpret_cast<char*>(&cols), sizeof(uint32_t));
    Nz_ext = rows;
    Nx_ext = cols;

    // Read array data
    size_t total_size = static_cast<size_t>(rows) * static_cast<size_t>(cols);
    vec1d<T> array(total_size, 0.0f);
    infile.read(reinterpret_cast<char*>(array.data()), total_size * sizeof(T));

    infile.close();
    return array;
}

int main() {
    // Define simulation parameters
    uint16_t Nx = 501, Nz = 501, Nt = 5001;
    float dx = 10.0f, dz = 10.0f, dt = 4.0e-4f;
    int pos0 = 50, posf = 50;
    float fmax = 10.0f;

    size_t Nx_ext = Nx + 8;
    size_t Nz_ext = Nz + 8;
    size_t total_size = Nx_ext * Nz_ext;

    // Initialize the source wavelet (property)
    vec1d<float> property = generateRicker(Nt, dt, fmax);

    // Initialize the model (velocity squared array)
    vec1d<float> model(total_size, 2500.0f); // Example constant velocity

    // Chamar compute_2D
    vec1d<float> result = compute_2D(property, Nx, Nz, Nt, dx, dz, dt, pos0, posf, model);

    // Export the result to a binary file
    std::string output_file = "wavefield_result.bin";
    exportBinaryFile1D(result, Nx_ext, Nz_ext, output_file);
    std::cout << "Wavefield result saved to " << output_file << std::endl;

    // Load the result back for verification
    size_t loaded_Nx_ext, loaded_Nz_ext;
    vec1d<float> loaded_result = loadBinaryFile1D<float>(output_file, loaded_Nx_ext, loaded_Nz_ext);
    std::cout << "Loaded wavefield dimensions: " << loaded_Nz_ext << "x" << loaded_Nx_ext << std::endl;

    return 0;
}


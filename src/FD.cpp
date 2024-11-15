#include "../include/imports.hpp"
#include "../include/common.hpp"
#include "../include/matrix.hpp"

// ensure that the user only use float type
class FD {
  public:
    vec1d<float> property;
    uint16_t Nx;
    uint16_t Nz;
    uint16_t Nt;
    float dx;
    float dz;
    int pos0;
    int posf;
    vec2D<float> model;

    vec2D<float> compute_2D() {
        vec2d<float> Upas(Nz, vec1d<float>(Nx, 0.0f));
        vec2d<float> Upre(Nz, vec1d<float>(Nx, 0.0f));
        vec2d<float> Ufut(Nz, vec1d<float>(Nx, 0.0f));

        for (size_t n = 0; n < Nt; n++) {
            Upre[pos0][posf] += property[n] / (dx * dx);

            vec2d<float> laplacian_2D = get_laplacian_2D(Upre);

            vec2d<float> model_squared = multMat(model, model);
            Ufut = multMat(laplacian_2D, scalarMat(dx*dx, model_squared)) + scalarMat(2.0f, Upre);
      
            Upas, Upre = Upre, Ufut
    
        return Ufut;
    }

    vec2d<float> get_laplacian_2D(const vec2d<float>& U) {
        vec2d<float> d2u_dx2(Nz, vec1d<float>(Nx, 0.0f));
        vec2d<float> d2u_dz2(Nz, vec1d<float>(Nx, 0.0f));

        for (size_t i = 4; i < Nz - 4; i++) {
            for (size_t j = 4; j < Nx - 4; j++) {
                d2u_dx2[i][j] = 
                    (-9 * U[i - 4][j] + 128 * U[i - 3][j] - 1008 * U[i - 2][j] + 
                     8064 * U[i - 1][j] - 14350 * U[i][j] + 8064 * U[i + 1][j] - 
                     1008 * U[i + 2][j] + 128 * U[i + 3][j] - 9 * U[i + 4][j]) / 
                    (5040.0f * dx * dx);

                d2u_dz2[i][j] = 
                    (-9 * U[i][j - 4] + 128 * U[i][j - 3] - 1008 * U[i][j - 2] + 
                     8064 * U[i][j - 1] - 14350 * U[i][j] + 8064 * U[i][j + 1] - 
                     1008 * U[i][j + 2] + 128 * U[i][j + 3] - 9 * U[i][j + 4]) / 
                    (5040.0f * dz * dz);
            }
        }
        return addMat(d2u_dx2, d2u_dz2) 
    }
};


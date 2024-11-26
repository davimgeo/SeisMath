#include <cstring>
#include "../include/SeisMath.hpp"

int main (int argc, char *argv[]) {
    uint16_t Nt = 101; 
    float dt = 0.01;
    float fmax = 10;
    vec1d<float> freqs = {10.0f, 15.0f, 40.0f, 45.0f};

    seismath::Wavelets waveletGenerator(Nt, dt, fmax, freqs);

    vec1d<float> ricker = waveletGenerator.generateRicker();
    vec1d<float> orsmby = waveletGenerator.generateOrmsby();

    seismath::calculateRuntime([&]() {
        auto result = seismath::add1DVec(ricker, orsmby);
    });

    vec2d<int> arr = {{1, 2, 3},
                      {4, 5, 6},
                      {7, 8, 9}};

    seismath::PlotParameters params;
    params.title = "Ricker Wavelet";
    params.xlabel = "Samples";
    params.ylabel = "Amplitude";

    seismath::plot1D(ricker, params);
    return 0;
}

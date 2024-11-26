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

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-p") == 0) {
            seismath::printPlot1D(ricker);
        }
    }

    seismath::calculateRuntime([&]() {
        auto result = seismath::add1DVec(ricker, orsmby);
    });

    return 0;
}

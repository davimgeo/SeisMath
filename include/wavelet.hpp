#ifndef WAVELET_HPP
#define WAVELET_HPP

#include <cstdint>
#include "common.hpp"

namespace seismath {

    class Wavelets {
    public:

        Wavelets(uint16_t Nt, float dt, float fmax, const vec1d<float>& freqs);

        vec1d<float> generateRicker() const;
            
        vec1d<float> generateOrmsby() const;

    private:
        uint16_t Nt;
        float dt;
        float fmax;
        vec1d<float> freqs;

};          
}

#endif // !WAVELET_HPP

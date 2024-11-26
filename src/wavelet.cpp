#include <cstdint>
#include <cmath>
#include "../include/functions/common.hpp"
#include "../include/functions/wavelet.hpp"

namespace seismath {

    template <typename T>
    static constexpr T sinc(T x) {
        if (x == T(0)) {
            return T(1);
        }
        return std::sin(x) / x;
    }

    Wavelets::Wavelets(uint16_t Nt, float dt, float fmax, const vec1d<float>& freqs)
        : Nt(Nt), dt(dt), fmax(fmax), freqs(freqs) {}

    vec1d<float> Wavelets::generateRicker() const {
        vec1d<float> wavelet(Nt);
        for (size_t i = 0; i < Nt; i++) {
          wavelet[i] = 0.0f; 
        } 

        float t0 = 2.0f * M_PI / fmax;

        for (size_t i = 0; i < Nt; i++) {
            float t = i * dt - t0;
            float arg = (M_PI * fmax * t) * (M_PI * fmax * t); 
            wavelet[i] = (1.0f - 2.0f * arg) * std::exp(-arg);
        }

        return wavelet;
    }
        
    vec1d<float> Wavelets::generateOrmsby() const {
        float t0 = (Nt * dt) / 2.0f;
        vec1d<float> wavelet(Nt);
        for (size_t i = 0; i < Nt; i++) {
            float t = i * dt - t0;
            float arg1 = pow(sinc(M_PI * freqs[3] * t), 2) * pow(M_PI * freqs[3], 2) / (M_PI * freqs[3] - M_PI * freqs[2]);
            float arg2 = pow(sinc(M_PI * freqs[2] * t), 2) * pow(M_PI * freqs[2], 2) / (M_PI * freqs[3] - M_PI * freqs[2]);
            float arg3 = pow(sinc(M_PI * freqs[1] * t), 2) * pow(M_PI * freqs[1], 2) / (M_PI * freqs[1] - M_PI * freqs[0]);
            float arg4 = pow(sinc(M_PI * freqs[0] * t), 2) * pow(M_PI * freqs[0], 2) / (M_PI * freqs[1] - M_PI * freqs[0]);
            wavelet[i] = (arg1 - arg2) - (arg3 - arg4);
        }
        return wavelet;
    }
}


#ifndef WAVELET_HPP
#define WAVELET_HPP

#include <cstdint>
#include "common.hpp"

vec1d<float> generateRicker(uint16_t Nt, float dt, float fmax);

vec1d<float> generateOrmsby(uint16_t Nt, float dt, const vec1d<float>& freqs);

#endif // !WAVELET_HPP

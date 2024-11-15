#include "imports.hpp"
#include "common.hpp"

vec1d<float> generateRicker(uint16_t Nt, float dt, float fmax);

vec1d<float> generateOrmsby(uint16_t Nt, float dt, const vec1d<float>& freqs);

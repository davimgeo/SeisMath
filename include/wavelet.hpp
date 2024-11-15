#include "imports.hpp"
#include "common.hpp"

vec1d<float> generateRicker(uint16_t Nt, float dt, uint16_t fmax);

vec1d<float> generateOrmsby(uint16_t Nt, float dt, const vec1d<float>& freqs);

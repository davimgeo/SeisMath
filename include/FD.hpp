#pragma once

#include "imports.hpp"
#include "common.hpp"

vec2d<float> compute_2D(const vec1d<float>& property, uint16_t Nx, uint16_t Nz, uint16_t Nt,
                        float dx, float dz, float dt, int pos0, int posf, const vec2d<float>& model);


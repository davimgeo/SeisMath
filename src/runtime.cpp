#include <functional>
#include <chrono>
#include <cstdio>
#include "../include/functions/runtime.hpp"

namespace seismath {

void calculateRuntime(const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now();

    func();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    printf("Runtime: %f miliseconds\n", elapsed.count() * 1e-5);
}

} // namespace seismath


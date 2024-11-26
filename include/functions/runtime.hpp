#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <functional>

namespace seismath {

void calculateRuntime(const std::function<void()>& func);

}

#endif // RUNTIME_HPP


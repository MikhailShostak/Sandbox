#pragma once

#include <vector>

template<typename Type, typename Allocator = std::allocator<Type>>
using Array = std::vector<Type, Allocator>;

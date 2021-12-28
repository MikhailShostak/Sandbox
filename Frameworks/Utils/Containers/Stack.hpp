#pragma once

#include <deque>

template<typename Type, typename Allocator = std::allocator<Type>>
using Stack = std::deque<Type, Allocator>;

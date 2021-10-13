#pragma once

#include <deque>

template<typename Type, typename Allocator = std::allocator<Type>>
using Queue = std::deque<Type, Allocator>;

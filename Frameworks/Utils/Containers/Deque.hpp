#pragma once

#include <deque>

template<typename Type, typename Allocator = std::allocator<Type>>
using Deque = std::deque<Type, Allocator>;

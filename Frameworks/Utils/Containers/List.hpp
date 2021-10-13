#pragma once

#include <list>

template<typename Type, typename Allocator = std::allocator<Type>>
using List = std::list<Type, Allocator>;

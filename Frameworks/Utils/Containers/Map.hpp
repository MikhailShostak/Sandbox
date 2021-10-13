#pragma once

#include <unordered_map>

template<typename Key, typename Type, typename Comparator = std::less<Key>, typename Allocator = std::allocator<std::pair<const Key, Type>>>
using Map = std::unordered_map<Key, Type, Comparator, Allocator>;

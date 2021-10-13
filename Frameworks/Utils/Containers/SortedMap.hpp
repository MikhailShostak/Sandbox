#pragma once

#include <map>

template<typename Key, typename Type, typename Comparator = std::less<Key>, typename Allocator = std::allocator<std::pair<const Key, Type>>>
using SortedMap = std::map<Key, Type, Comparator, Allocator>;

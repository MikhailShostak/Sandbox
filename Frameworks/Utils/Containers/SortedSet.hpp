#pragma once

#include <set>

template<typename Key, typename Comparator = std::less<Key>, typename Allocator = std::allocator<Key>>
using SortedSet = std::set<Key, Comparator, Allocator>;

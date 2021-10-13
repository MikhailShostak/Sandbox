#pragma once

#include <unordered_set>

template<typename Key, typename Comparator = std::less<Key>, typename Allocator = std::allocator<Key>>
using Set = std::unordered_set<Key, Comparator, Allocator>;

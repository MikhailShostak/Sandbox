#pragma once

#include <unordered_set>

template<typename Key, typename Hasher = std::hash<Key>, typename Comparator = std::equal_to<Key>, typename Allocator = std::allocator<Key>>
using Set = std::unordered_set<Key, Hasher, Comparator, Allocator>;

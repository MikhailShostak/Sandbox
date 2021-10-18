#pragma once

#include <unordered_map>

template<typename Key, typename Type, typename KeyHasher = std::hash<Key>, typename KeyComparator = std::equal_to<Key>, typename Allocator = std::allocator<std::pair<const Key, Type>>>
using Map = std::unordered_map<Key, Type, KeyHasher, KeyComparator, Allocator>;

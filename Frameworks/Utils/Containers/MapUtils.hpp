#pragma once

#include "Map.hpp"
#include "SortedMap.hpp"

namespace MapUtils
{

template<class Key, class T, class Compare, class Alloc, class Pred>
inline typename SortedMap<Key, T, Compare, Alloc>::size_type EraseIf(SortedMap<Key, T, Compare, Alloc>& c, Pred pred)
{
    auto old_size = c.size();
    for (auto i = c.begin(), last = c.end(); i != last; )
    {
        if (pred(*i))
        {
            i = c.erase(i);
        }
        else
        {
            ++i;
        }
    }
    return old_size - c.size();
}

template<class Key, class T, class Compare, class Alloc, class Pred>
inline typename Map<Key, T, Compare, Alloc>::size_type EraseIf(Map<Key, T, Compare, Alloc>& c, Pred pred)
{
    auto old_size = c.size();
    for (auto i = c.begin(), last = c.end(); i != last; )
    {
        if (pred(*i))
        {
            i = c.erase(i);
        }
        else
        {
            ++i;
        }
    }
    return old_size - c.size();
}

}

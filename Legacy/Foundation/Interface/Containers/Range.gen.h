#pragma once
#include <range/v3/all.hpp>

namespace rng {
    using namespace ranges;
}

namespace rngv {
    using namespace ranges::views;
}

template<typename Type>
using Range = rng::any_view<Type>;

template<class T>
struct remove_cvref {
    typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};

template<class T>
using remove_cvref_t = typename remove_cvref<T>::type;

template<class range_type>
struct cache_view : ranges::view_facade<cache_view<range_type>>
{
private:
    friend ranges::range_access;
    using value_type = ranges::range_value_t<range_type>;
    std::vector<value_type> cache;
    struct cursor
    {
    private:
        typename std::vector<value_type>::iterator iter;
    public:
        using contiguous = std::true_type;
        cursor() = default;
        cursor(typename std::vector<value_type>::iterator it)
            : iter(it)
        {}
        int const &read() const
        {
            return *iter;
        }
        bool equal(cursor const &that) const
        {
            return iter == that.iter;
        }
        void next()
        {
            ++iter;
        }
        void prev()
        {
            --iter;
        }
        std::ptrdiff_t distance_to(cursor const &that) const
        {
            return that.iter - iter;
        }
        void advance(std::ptrdiff_t n)
        {
            iter += n;
        }
    };
    cursor begin_cursor()
    {
        return { cache.begin() };
    }
    cursor end_cursor()
    {
        return { cache.end() };
    }
public:
    cache_view()
    {

    }

    cache_view(range_type &&input)
    {
        std::move(input.begin(), input.end(), std::back_inserter(cache));
    }
};

template<class T>
auto make_cache(T &&data) { return cache_view<remove_cvref_t<T>>{std::move(data)}; }

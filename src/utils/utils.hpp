#pragma once
#include "../iterators/randomAccessIt.hpp"

namespace ft{
    template <class T>
    size_t distance(T first, T last)
    {
        size_t r = 0;
        for (; first != last; ++first)
            ++r;
        return r;
    }
}
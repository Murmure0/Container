#pragma once

#include <cstddef>

namespace ft{
    
    template <class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
        class Iterator {
            public:
                typedef T         value_type;
                typedef Distance  difference_type; // std::ptrdiff_t is the signed integer type of the result of subtracting two pointers.
                typedef Pointer   pointer;
                typedef Reference reference;
                typedef Category  iterator_category;
    };
}

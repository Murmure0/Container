#pragma once

#include "iterator.hpp"

namespace ft{

    class input_iterator_tag  {};
    class output_iterator_tag {};
    class forward_iterator_tag       : public input_iterator_tag         {};
    class bidirectional_iterator_tag : public forward_iterator_tag       {};
    class random_access_iterator_tag : public bidirectional_iterator_tag {};

    template<class Iterator>
    class iterator_traits
    {
        public:
            typedef typename Iterator::difference_type      difference_type;
            typedef typename Iterator::value_type           value_type;
            typedef typename Iterator::pointer              pointer;
            typedef typename Iterator::reference            reference;
            typedef typename Iterator::iterator_category    iterator_category;
    };

    template<class T>
    class ft::iterator_traits<T *>
    {
        public:
            typedef ptrdiff_t                   difference_type;
            typedef T                           value_type;
            typedef T*                          pointer;
            typedef T&                          reference;
            typedef random_access_iterator_tag  iterator_category;
    };

    template<class T>
    class ft::iterator_traits<const T *>
    {
        public:
            typedef ptrdiff_t                   difference_type;
            typedef T                           value_type;
            typedef T*                          pointer;
            typedef T&                          reference;
            typedef random_access_iterator_tag  iterator_category;
    };
}
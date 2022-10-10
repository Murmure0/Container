#pragma once
#include <iostream>
#include "vector.hpp"

namespace ft{

    template < class T, class Container = ft::vector<T> > 
    class stack
    {
        public :

        typedef Container   container_type;
        typedef typename container_type::value_type      value_type;
        typedef typename container_type::reference       reference;
        typedef typename container_type::const_reference const_reference;
        typedef typename container_type::size_type       size_type;

        protected :
        container_type c;


        public:

        explicit stack (): c() {}
        explicit stack (const container_type& ctnr = container_type()): c(ctnr,) {}
    };
}
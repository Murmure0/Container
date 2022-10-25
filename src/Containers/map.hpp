#pragma once
#include <map>
#include "../utils/binary_function.hpp"
#include "../utils/pair.hpp"



namespace ft{

    template < class Key, class T, class Compare = ft::less<Key>,
            class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map{

        typedef Key                                      key_type;
        typedef T                                        mapped_type;
        typedef pair<const key_type, mapped_type>        value_type;
        typedef Compare                                  key_compare;
        typedef Alloc                                    allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        // typedef implementation-defined                   iterator;
        // typedef implementation-defined                   const_iterator;
        // typedef std::reverse_iterator<iterator>          reverse_iterator;
        // typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
    };

    // Nested class value_compare to use the Compare class given 
    // class value_compare : public ft::binary_function<value_type, value_type, bool>()
    // {


    // };
}
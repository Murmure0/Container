#pragma once
#include "../utils/binary_function.hpp"
#include "../utils/pair.hpp"
#include "../utils/redBlackTree.hpp"
#include "../iterators/treeIterator.hpp"

#include <iostream>

/*
    key_compare key_comp(); //par defaut std::less
    rbtree<int> -> key_comp(1, 5) --> bool qui dit si 1 < 5

    rbtree< pair<int, int> > -> key_comp(pair(1, 5), pair(5, 2)) --> key_comp n'est pas prevu pour ca 
    //pour map en interne on peut faire ca :
    key_comp(pair.first, autrePair.first); //compare des ints a nouveau
    //a la place on fait ca plutot
    value_compare val_comp();
    val_comp(pair, autrePair);

    //en interne en gros:
    val_comp(key_comp, pair, autrePair)
    {
        return key_comp(pair.first, autrePair.first);
    }

*/

namespace ft{

    template < class Pair, class Compare, class Alloc, class Node>
    class treeIterator;
    template < class Key, class T, class Compare = ft::less<Key>,
            class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map{
        public :

            // CLASSES

            class value_compare : public ft::binary_function< pair<const Key, T>, pair<const Key, T>, bool >
            {
                friend class map;

                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

                public:
            
                bool operator() (const pair<const Key, T>& x, const pair<const Key, T>& y) const
                {
                    return comp(x.first, y.first); // use Compare based on ft::less, on the key of the pair
                }
            };

            typedef Key                                                 key_type;
            typedef T                                                   mapped_type;
            typedef pair<const Key, T>                                  value_type;
            typedef Compare                                             key_compare;
            typedef Alloc                                               allocator_type;
            typedef typename allocator_type::reference                  reference;
            typedef typename allocator_type::const_reference            const_reference;
            typedef typename allocator_type::pointer                    pointer;
            typedef typename allocator_type::const_pointer              const_pointer;
            typedef typename allocator_type::size_type                  size_type;
            typedef typename allocator_type::difference_type            difference_type;
            typedef ft::BsT<value_type, value_compare, Alloc>           tree_type;
            typedef ft::BsT<const value_type, value_compare, Alloc>     const_tree_type;
            typedef typename tree_type::node                            node_type;
            typedef typename const_tree_type::node                      const_node_type;

            typedef ft::treeIterator< value_type, value_compare, allocator_type, node_type >                   iterator;
            typedef ft::treeIterator< const value_type, value_compare, allocator_type, const_node_type>        const_iterator;
            typedef std::reverse_iterator<iterator>                                                            reverse_iterator;
            typedef std::reverse_iterator<const_iterator>                                                      const_reverse_iterator;
        

            /* Constructor/destructor */

            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
                : _key_comp(key_compare), _size(0), _value_compare(_key_comp) {
                    std::cout << "A MAP HAVE BEEN CONSTRUCTED" << std::endl;    
            }

            // template <class It>
            // map (It first, It last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _key_comp(key_compare), _value_comp(_key_comp) {

            //     for(;first != end; first++){
            //         _tree.insertNode(first); //mon insert ne fonctionne que sur des pairs prrff
            //     }
            // }

            map (const map& x){
                *this = x;
            }


            ~map(){}

            map& operator= (const map& x){
                _size = x._size;
                _tree = x._tree;
                return *this;
            }

            iterator begin(){
                return (_tree.begin()); 
            }

            const_iterator begin() const{
                return (_tree.begin()); 
            }

            iterator end(){
                return (_tree.end());
            }

        private :

            BsT<value_type, value_compare, Alloc> _tree;
            size_type _size;
            key_compare _key_comp;
            value_compare _value_comp;
    };



}
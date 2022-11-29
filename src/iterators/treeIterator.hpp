#pragma once
#include "../containers/map.hpp"
#include "../utils/redBlackTree.hpp"
#include "../utils/binary_function.hpp"
#include "itTraits.hpp"

namespace ft{


    template <class T, class Compare, class Alloc>
    class BsT;


    template < class Pair, class Compare = ft::less< Pair>, class Alloc = std::allocator<Pair> , class node = typename ft::BsT < Pair, Compare, Alloc >::node>
    class treeIterator
    {
        public:
            typedef ft::treeIterator< Pair, Compare, Alloc, node>   iterator;
            typedef ft::treeIterator< const Pair, Compare, Alloc, typename ft::BsT< const Pair, Compare, Alloc >::node > const_iterator;

            typedef Pair           value_type;
            typedef ptrdiff_t      difference_type;
            typedef Pair*              pointer;
            typedef Pair&            reference;
            typedef  typename ft::Iterator<ft::bidirectional_iterator_tag, Pair>::iterator_category    iterator_category;

            treeIterator(){
                return ;}
                
            ~treeIterator() {return ;}

            treeIterator(treeIterator const &src) : _node(src._node) { return ;}

            treeIterator(node *n) : _node(n) {return ;}

            treeIterator &operator=(treeIterator const &rhs){
                _node = rhs._node;
                return *this;
            }

            // Operators

            Pair& operator*() const{
                return (_node->pair);
            }

            Pair* operator->() const{ 
                return (&_node->pair);
            }

            treeIterator& operator++(){
                _node = _node->findNext(); 

                return (*this);
            }

            treeIterator  operator++(int){
                treeIterator tmp(*this);
                _node = _node->findNext();
                return tmp;
            }

            treeIterator& operator--(){
                _node = _node->findPrevious();
                return (*this);
            }

            treeIterator  operator--(int){
                treeIterator tmp(*this);
                _node = _node->findPrevious();
                return tmp;
            }

            // Const caster

            //const_iterator -> iterator on const pair
            //const iterator -> const iterator on pair
            //const const_iterator -> const iterator on const pair

            operator			const_iterator() const{
                const iterator &it = *this;
                return reinterpret_cast<const const_iterator & >(it);
            }

            node* const &base() const{return _node;}
        
            bool getComp(Pair lhs, Pair rhs) const{return _node->comp(lhs, rhs);}


        private:

            node*    _node;
    };
    
            template <class Pair1, class Pair2, class Compare, class Alloc, class Node1, class Node2>
            bool operator== (const treeIterator< Pair1, Compare, Alloc, Node1 >& lhs, const treeIterator<Pair2, Compare, Alloc, Node2>& rhs){
                return ( lhs.base() == reinterpret_cast<Node1*>(rhs.base()) );
            }

            template <class Pair1, class Pair2, class Compare, class Alloc, class Node1, class Node2>
            bool operator != (const treeIterator<Pair1, Compare, Alloc, Node1>& lhs, const treeIterator<Pair2, Compare, Alloc, Node2>& rhs){
                return !(lhs == rhs);
            }

}


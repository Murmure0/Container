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
            typedef ft::treeIterator< const Pair, Compare, Alloc, const typename ft::BsT< const Pair, Compare, Alloc >::node > const_iterator;

            typedef Pair           value_type;
            typedef ptrdiff_t      difference_type;
            typedef Pair*              pointer;
            typedef Pair&            reference;
            typedef  typename ft::Iterator<ft::bidirectional_iterator_tag, Pair>::iterator_category    iterator_category;

            treeIterator(){
                return ;}
                
            ~treeIterator() {return ;}

            treeIterator(treeIterator const &src){
                *this = src;
            }

            treeIterator(node *n) : _node(n) {return ;}

            treeIterator &operator=(treeIterator const &rhs){
                _node = rhs._node; // ne copie pas la paire du node ?
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
                
                // std::cout << _node->pair.first << std::endl;
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

            operator			const_iterator() const{
                const iterator &it = *this;
                return reinterpret_cast<const_iterator & >(it);
		        // return reinterpret_cast<treeIterator<const Pair, Compare, typename BsT<const Pair, Compare, Alloc>::node > & >(it);
            }

			// operator			node_pointer() const;

            node* const &base() const{return _node;}

        
            bool getComp(Pair lhs, Pair rhs) const{return _node->comp(lhs, rhs);}


        private:

            node*    _node;
    };


            template <class Pair, class Compare, class Alloc, class node>
            bool operator== (const treeIterator< Pair, Compare, Alloc, node >& lhs, const treeIterator<Pair, Compare, Alloc, node>& rhs){
                return ( lhs.base() == rhs.base() );
                // !lhs.getComp(lhs.base()->pair, rhs.base()->pair)
                // &&
                // !rhs.getComp(rhs.base()->pair, lhs.base()->pair));
            }

            template <class Pair, class Compare, class Alloc, class node>
            bool operator != (const treeIterator<Pair, Compare, Alloc, node>& lhs, const treeIterator<Pair, Compare, Alloc, node>& rhs){
                return !(lhs == rhs);
            }

}


#pragma once
#include "../containers/map.hpp"
#include "../utils/redBlackTree.hpp"
#include "../utils/binary_function.hpp"

namespace ft{


    template <class T, class Compare, class Alloc>
    class BsT;


    template < class Pair, class Compare = ft::less< Pair>, class Alloc = std::allocator<Pair> , class Node = typename ft::BsT < Pair, Compare, Alloc >::node>
    class treeIterator
    {
        public:

            treeIterator(){
                return ;}
                
            ~treeIterator() {return ;}

            treeIterator(treeIterator const &src){
                *this = src;
            }
            treeIterator(Node *n) : _node(n) {return ;}

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

            operator			treeIterator< const Pair, Compare, Alloc, Node >() const{
                const treeIterator &it = *this;
		        return reinterpret_cast<const treeIterator<const Pair, Compare, Node > & >(it);
            }

			// operator			node_pointer() const;

            Node* const &base() const{return _node;}

        
            Compare getComp() const{return _node->comp;}


        private:

            Node*    _node;
    };


            template <class Pair, class Compare, class Alloc, class Node>
            bool operator== (const treeIterator< Pair, Compare, Alloc, Node >& lhs, const treeIterator<Pair, Compare, Alloc, Node>& rhs){
                return !lhs.getComp(lhs.base().pair, rhs.base().pair) && !rhs.getComp(rhs.base().pair, lhs.base().pair);
                // return !_comp(lhs._node->pair, rhs._node->pair) && !_comp(rhs._node->pair, lhs._node->pair);
            }

            template <class Pair, class Compare, class Alloc, class Node>
            bool operator != (const treeIterator<Pair, Compare, Alloc, Node>& lhs, const treeIterator<Pair, Compare, Alloc, Node>& rhs){
                return !(lhs == rhs);
            }

}


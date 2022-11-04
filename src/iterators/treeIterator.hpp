#pragma once
#include "../containers/map.hpp"
#include "../utils/redBlackTree.hpp"

namespace ft{
    template < class Pair, class Compare = ft::less<Pair>, class Alloc = std::allocator<Pair> , class Node = typename ft::BsT < Pair, Compare, Alloc >::node, class BsT = typename ft::BsT< Pair, Compare, Alloc > >
    class treeIterator
    {
        public:

            treeIterator() {return ;};
            ~treeIterator() {return ;};

            treeIterator(treeIterator const &src){
                *this = src;
            }
            treeIterator(Node *n) : _node(n->pair), _comp(Compare()){return ;}

            treeIterator &operator=(treeIterator const &rhs){
                _comp = rhs._comp;
                _node = rhs._node;
            }

            // Operators

            treeIterator& operator*() const{
                return (_node->pair);
            }

            treeIterator* operator->() const{ 
                return (&_node->pair);
            }

            treeIterator& operator++(){
                _node = _tree.findNext(_node); 
                return (*this);
            }

            treeIterator  operator++(int){
                treeIterator tmp(*this);
                _node = _tree.findNext(_node);
                return tmp;
            }

            treeIterator& operator--(){
                _node = _tree.findPrevious(_node);
                return (*this);
            }

            treeIterator  operator--(int){
                treeIterator tmp(*this);
                _node = _tree.findPrevious(_node);
                return tmp;
            }

            // Const caster

            // operator			treeIterator< const Pair, Compare, Alloc, Node >() const;
			// operator			node_pointer() const;

            Node* const &base() const{return _node;}

        private:

            Node*    _node;
            Compare  _comp;
            BsT     _tree;
    };


            template <class Pair, class Compare, class Alloc, class Node>
            bool operator== (const treeIterator< Pair, Compare, Alloc, Node >& lhs, const treeIterator<Pair, Compare, Alloc, Node>& rhs){
                return !_comp(lhs._node->pair, rhs._node->pair) && !_comp(rhs._node->pair, lhs._node->pair);
            }

            template <class Pair, class Compare, class Alloc, class Node>
            bool operator != (const treeIterator<Pair, Compare, Alloc, Node>& lhs, const treeIterator<Pair, Compare, Alloc, Node>& rhs){
                return !(lhs == rhs);
            }

}


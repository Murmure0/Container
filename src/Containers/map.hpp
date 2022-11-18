#pragma once
#include "../utils/lex.hpp"
#include "../utils/pair.hpp"
#include "../utils/redBlackNode.hpp"
#include "../utils/redBlackTree.hpp"
#include "../iterators/treeIterator.hpp"
#include "../iterators/reverseIt.hpp"

namespace ft{
   template <class T, class Compare, class Alloc>
    class BsT;

    template < class Pair, class Compare, class Alloc, class Node>
    class treeIterator;

    template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
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
            typedef ft::reverse_iterator< iterator >                                                            reverse_iterator;
            typedef ft::reverse_iterator< const_iterator >                                                      const_reverse_iterator;

        private :

            BsT<value_type, value_compare, Alloc> _tree;
            size_type _size;
            key_compare _key_comp;
            value_compare _value_comp;
            Alloc _alloc;
        

        public :

            /* ---------------CONSTRUCTOR/DESTRUCTOR--------------- */

            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
                : _tree(_value_comp), _size(0), _key_comp(comp), _value_comp(comp), _alloc(alloc) {
            }

            template <class It>
            map (It first, It last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
                : _tree(_value_comp), _size(0), _key_comp(comp), _value_comp(comp), _alloc(alloc) {
                insert(first, last);
            }

            //SEE YOU LATER
            map (const map& x) : _tree(x._tree), _size(x._size), _key_comp(x._key_comp), _value_comp(x._value_comp), _alloc(x._alloc)
            {
                return ;
            }


            ~map(){}


            /*---------OPERTOR OVERLOADS-----------*/

            map& operator= (const map& x){
                _size = x._size;
                _tree = x._tree;
                return *this;
            }

            mapped_type& operator[] (const key_type& k){
                value_type p(k, mapped_type());

                pair<iterator, bool> ret = this->insert(p);
                return ret.first->second;
            }


            /*--------------UTILS---------------*/

            iterator begin(){
                return _tree.findMin();
            }

            const_iterator begin() const{
                return reinterpret_cast<const_node_type*>(_tree.findMin());
            }

            iterator end(){
                return (_tree.getEnd());
            }

            const_iterator end() const{
                return reinterpret_cast< const_node_type* >(_tree.getEnd());
            }

            reverse_iterator rbegin(){
                iterator it = static_cast<iterator>(_tree.getEnd());
                return static_cast<reverse_iterator>(it);
            }

            const_reverse_iterator rbegin() const{
                return static_cast<const_iterator>(reinterpret_cast< const_node_type* >(_tree.getEnd()));
            }
            
            reverse_iterator rend(){
                iterator it = static_cast<iterator>(_tree.findMin());
                return static_cast<reverse_iterator>(it);
            }

            const_reverse_iterator rend() const{
                return static_cast<const_iterator>(reinterpret_cast< const_node_type* >(_tree.findMin()));
            }

            bool empty() const{
                return (!_size);
            }

            size_type size() const{
                return (_size);
            }

            size_type max_size() const{
                return (_alloc.max_size());
            }

            pair<iterator,bool> insert (const value_type& val){
                pair<iterator, bool> ret;

                ret = _tree.insert_val(val);
                if (ret.second)
                    _size++;
                return ret;
            }

            iterator insert (iterator position, const value_type& val){
                node_type* hint  = position.base();
                
                node_type* ret = _tree.insertHint(hint, val);
                if (ret)
                    _size++;
                return ret;

            }

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last){
                for(; first != last; first++){
                    pair<iterator, bool> ret = _tree.insert_val(*first);
                    if (ret.second == true)
                        _size++;
                }
            }

            void erase (iterator position){
                if (_tree.findNode(*position))
                {
                    _tree.deleteNode(position.base());
                    _size--;
                }
            }

            size_type erase (const key_type& k){
                if (_tree.deleteNode(ft::make_pair(k, mapped_type()))){
                    _size--;
                    return 1;
                }
                else
                    return 0;
            }

            void erase (iterator first, iterator last){
                for(;first != last; first++){
                    erase(first);
                }
            }

            void swap (map& x){
                node_type*  tmp_end = this->_tree.getEnd();
                node_type*  tmp_root = this->_tree.getRoot();
                size_t      tmp_size = this->_size;

                this->_tree.setRoot(x._tree.getRoot());
                this->_tree.setEnd(x._tree.getEnd());
                this->_size = x._size;

                x._tree.setRoot(tmp_root);
                x._tree.setEnd(tmp_end);
                x._size = tmp_size;
            }

            void clear(){
                _tree.clear();
                _size = _tree.getSize();
            }

            key_compare key_comp() const{
                return _key_comp;
            }

            value_compare value_comp() const{
                return _value_comp;
            }

            iterator find (const key_type& k){
                value_type p(k, mapped_type());

                return (_tree.findNode(p));
            }

            const_iterator find (const key_type& k) const{
               value_type p(k, mapped_type());

                return reinterpret_cast<const_node_type*>(_tree.findNode(p));
            }

            size_type count (const key_type& k) const{
               value_type p(k, mapped_type());

                return(_tree.count(p));
            }

            iterator lower_bound (const key_type& k)    /*Returns an iterator pointing to the first element in the container whose key 
                                                            is not considered to go before k (i.e., either it is equivalent or goes after).*/
            {
               value_type p(k, mapped_type());
                return (_tree.lower_bound(p));
            } 

            const_iterator lower_bound (const key_type& k) const{
               value_type p(k, mapped_type());
                return reinterpret_cast<const_node_type*>(_tree.lower_bound(p));
            }

            iterator upper_bound (const key_type& k){
               value_type p(k, mapped_type());
                return (_tree.upper_bound(p));
            }

            const_iterator upper_bound (const key_type& k) const{
               value_type p(k, mapped_type());
                return reinterpret_cast<const_node_type*>(_tree.upper_bound(p));
            }
            
            pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
                return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
            }

            pair<iterator,iterator>             equal_range (const key_type& k){
                return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
            }

            allocator_type get_allocator() const{return _value_comp;}
    };

 /* RELATIONAL OPERATORS */
    template <class Key, class T, class Compare, class Alloc>  bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
        return ( lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class Key, class T, class Compare, class Alloc>  bool operator!= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
        return (!(lhs == rhs));
    }

    template <class Key, class T, class Compare, class Alloc>  bool operator<  (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class Key, class T, class Compare, class Alloc>  bool operator<= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
        return (!(rhs < lhs));
    }

    template <class Key, class T, class Compare, class Alloc>  bool operator>  (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
        return (!(lhs <= rhs));
    }

    template <class Key, class T, class Compare, class Alloc>  bool operator>= (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs){
        return(!(lhs < rhs));
    }

    /* SWAP FUNCTION*/
    template <class Key, class T, class Compare, class Alloc>  void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y){
        x.swap(y);
    }


}
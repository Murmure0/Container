#pragma once
#include "../utils/binary_function.hpp"
#include "../utils/pair.hpp"
#include "../utils/redBlackTree.hpp"
#include "../iterators/treeIterator.hpp"
#include "../utils/binary_function.hpp"

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
            typedef std::reverse_iterator<iterator>                                                            reverse_iterator;
            typedef std::reverse_iterator<const_iterator>                                                      const_reverse_iterator;
        

            /* Constructor/destructor */

            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
                : _tree(_value_comp), _size(0), _key_comp(comp), _value_comp(comp), _alloc(alloc) {

                    std::cout << "A MAP HAVE BEEN CONSTRUCTED, YEAY !!!" << std::endl;    
            
            }

            template <class It>
            map (It first, It last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
                : _tree(_value_comp), _size(0), _key_comp(comp), _value_comp(comp), _alloc(alloc) {
                insert(first, last);
            }

            //SEE YOU LATER
            // map (const map& x){
            //     *this = x;
            // }


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

            const_iterator end() const{
                return (_tree.end());
            }

            reverse_iterator rbegin(){
                return(_tree.rbegin());
            }

            const_reverse_iterator rbegin() const{
                return(_tree.rbegin());
            }
            
            reverse_iterator rend(){
                return (_tree.end());
            }

            const_reverse_iterator rend() const{
                return (_tree.end());
            }

            bool empty() const{
                return (_size);
            }

            size_type size() const{
                return (_size);
            }

            size_type max_size() const{
                return (_alloc.max_size());
            }

            mapped_type& operator[] (const key_type& k){
                pair<key_type, int> p(k, 0);
                return (_tree.findNode(p)->pair.second);
            }

            pair<iterator,bool> insert (const value_type& val){
                pair<iterator, bool> ret;

                ret = _tree.insertVal(val);
                _size++;
                return ret;
            }

            iterator insert (iterator position, const value_type& val){
                
                pair<iterator, bool> ret;

                node_type* hint  = *position;
                ret = _tree.insertHint(hint, val);

            }

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last){
                for(; first != last; first++){
                    pair<iterator, bool> ret = _tree.insertVal((*first).pair);
                    if (ret.second == true)
                        _size++;
                }
            }

            void erase (iterator position){
                _tree.deleteNode(position.base());
                    _size--;
            }

            size_type erase (const key_type& k){
                if (_tree.deleteNode(make_pair(k, 0))){
                    _size--;
                    return 1;
                }
                else
                    return 0;
            }

            void erase (iterator first, iterator last){
                for(;first != last; first++){
                    erase(first);
                    _size--;
                }
            }

            void swap (map& x){
                map *tmp = this;
                this = x;
                x = tmp;
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
                pair<key_type, int> p(k, 0);

                return iterator(_tree.findNode(p));
            }

            const_iterator find (const key_type& k) const{
                pair<key_type, int> p(k, 0);

                return const_iterator(_tree.findNode(p));
            }

            size_type count (const key_type& k) const{
                pair<key_type, int> p(k, 0);

                return(_tree.count(p));
            }

            iterator lower_bound (const key_type& k)    /*Returns an iterator pointing to the first element in the container whose key 
                                                            is not considered to go before k (i.e., either it is equivalent or goes after).*/
            {
                pair<key_type, int> p(k, 0);
                return (_tree.lower_bound(p));
            } 

            const_iterator lower_bound (const key_type& k) const{
                pair<key_type, int> p(k, 0);
                return (_tree.lower_bound(p));
            }

            iterator upper_bound (const key_type& k){
                pair<key_type, int> p(k, 0);
                return (_tree.upper_bound(p));
            }

            const_iterator upper_bound (const key_type& k) const{
                pair<key_type, int> p(k, 0);
                return (_tree.upper_bound(p));
            }
            
            pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
                return _tree.equal_range(k);
            }

            pair<iterator,iterator>             equal_range (const key_type& k){
                    return _tree.equal_range(k);
            }

            allocator_type get_allocator() const{return _value_comp;}

        private :

            BsT<value_type, value_compare, Alloc> _tree;
            size_type _size;
            key_compare _key_comp;
            value_compare _value_comp;
            Alloc _alloc;
    };



}
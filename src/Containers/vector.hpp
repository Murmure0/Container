#pragma once

#include "../iterators/randomAccessIt.hpp"
#include "../iterators/itTraits.hpp"
#include "../iterators/reverseIt.hpp"
#include "../utils/lex.hpp"
#include "../utils/type_traits.hpp"
#include "../utils/utils.hpp"
#include <memory>
#include <iostream>
#include <vector>




namespace ft{

    template < class T, class Alloc = std::allocator<T> > 
    class vector
    {
        public :

            typedef T                                                           value_type;
            typedef Alloc                                                       allocator_type;
            typedef typename allocator_type::reference                          reference;
            typedef typename allocator_type::const_reference                    const_reference;
            typedef typename allocator_type::pointer                            pointer;
            typedef typename allocator_type::const_pointer                      const_pointer;
            typedef typename ft::random_access_iterator<T>                      iterator;
            typedef typename ft::random_access_iterator<const T>                const_iterator;
            typedef typename ft::reverse_iterator<iterator>                     reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>               const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type     difference_type;
            typedef size_t                                                      size_type;

        private:

            size_type   _size;
            size_type   _capacity;
            pointer     _content;
            Alloc       _alloc;

        public:

            /* CONSTRUCTORS & DESTRUCTOR */

            /* empty container constructor (default constructor), constructs an empty container, with no elements. */
            explicit vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _content(NULL), _alloc(alloc){ return ; }

            /* fill constructor, constructs a container with n elements. Each element is a copy of val. */
            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){
                _size = _capacity = n;
                _alloc = alloc;
                _content = _alloc.allocate(n);
                while(n--)
                    _alloc.construct(_content + n, val);
                return ;
            }	

            /* range constructor, constructs a container with as many elements as the range [first,last), 
            with each element constructed from its corresponding element in that range, in the same order. */

            /* 
                SFINAE & enable_if : 
                " We want to write a template that only makes sense for some types, 
                we must make it fail deduction for invalid types right in the declaration, to cause substitution failure. 
                If the invalid type sneaks past the overload candidate selection phase, the program won't compile. "
            
                Integral type as parameter : 
                we don't want the compilation to fail because of the template for the Iterator, 
                so we use enable_if :
                    The template will be used only if ::type existe in the integral_constant struct, 
                    ::type is typedef only if the param given is an iterator

                    enable_if<true> -> possede un typedef type
                
                    enable_if<false>::type n'existe pas 

                    enable_if<ft::is_integral<InputIterator>::value>::type is true(integral) or false(iterator)
                        it would compile with this template if an integral was given
                    enable_if<!ft::is_integral<InputIterator>::value>::type allow to compile want the param is NOT a integral, 
                    so this template is checked and used only if an iterator is in param 
            */

            template <class InputIterator> 
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL){
                _alloc = alloc;
                _size = _capacity = ft::distance(first, last);
                _content = _alloc.allocate(_size);
                for(size_t i = 0; first != last; first++, i++)
                {
                    _alloc.construct(_content + i, *first);
                }
            }

            /* copy constructor, constructs a container with a copy of each of the elements in x, in the same order. */
            vector (const vector& x){
                _capacity = _size = x.size();
                _alloc = x.get_allocator();
                _content = _alloc.allocate(_size);
                const_iterator first = x.begin();
                const_iterator end = x.end();
                for (size_t i = 0; first != end; first++, i++)
                    _alloc.construct(_content + i, *first);
            }

            /* destroys all container elements, and deallocates all the storage capacity allocated 
                by the vector using its allocator. */
            ~vector(){
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_content + i);
                _alloc.deallocate(_content, _capacity);
            }
            
            /* Copies all the elements from x into the container. */
            vector& operator= (const vector& x){
                for (size_type i = 0; i < _size; i++){
                    _alloc.destroy(_content + i);
                }
                _alloc.deallocate(_content, _capacity);

                _capacity = _size = x.size();
                _content = _alloc.allocate(_size);
                const_iterator first = x.begin();
                const_iterator end = x.end();
                for (size_t i = 0; i < _size; first++, i++){
                    _alloc.construct(_content + i, *first);
                }
                return *this;
            }

            /* ITERATORS */
            iterator begin(){ return _content; }
            const_iterator begin() const { return _content; }
            iterator end(){ return (_content + _size); }
            const_iterator end() const { return (_content + _size); }
            reverse_iterator rbegin(){ return reverse_iterator(end()); }
            const_reverse_iterator rbegin() const{ return const_reverse_iterator(end()); }
            reverse_iterator rend(){ return reverse_iterator(begin()); }
            const_reverse_iterator rend() const{ return const_reverse_iterator(begin()); }


            /* CAPACITY */
            size_type size() const{ return _size; }

            /* Returns the maximum number of elements, each of member type value_type (an alias of allocator's template parameter)
                that could potentially be allocated by a call to member allocate.
                A call to member allocate with the value returned by this function can still fail to allocate the requested storage. */    
            size_type max_size() const{ return _alloc.max_size(); }

            /* A TEST UNE FOIS PUSHBACK FAIT */
            void resize(size_type n, value_type val = value_type()){
                if (n < _size)
                {
                    for (size_type i = n; i < _size; i++){
                        _alloc.destroy(_content + i);
                    }
                    _size = n;
                }
                else if (n > _size)
                {
                    if (n > _capacity){
                        reserve(n);
                    }
                    size_t previous_size = _size; 
                    _size = n;
                    for(size_t  i = previous_size; i < n; i++){
                        _alloc.construct(_content + i, val);
                    }
                    
                }
            }


            size_type capacity() const{ return _capacity; };
            bool empty() const { return _size == 0; }

            /* Requests that the vector capacity be at least enough to contain n elements. */
            void reserve(size_type n){
                if (n > _capacity)
                {
                    pointer newVector = _alloc.allocate(n);
                    iterator it = begin();
                    iterator ite = end();
                    for (int i = 0; it != ite; it++, i++)
                        _alloc.construct(newVector + i, *it);
                    for (size_type i = 0; i < _size; i++)
                        _alloc.destroy(_content + i);
                    _alloc.deallocate(_content, _capacity);
                    _content = newVector;
                    _capacity = n;
                }
            }

            /* ELEMENT ACCESS */
            reference operator[] (size_type n){ return *(_content + n);}
            const_reference operator[] (size_type n) const{ return *(_content + n);}
            reference at (size_type n){ 
                if (n >= _size)
                    throw std::out_of_range("ft::vector");
                return *(_content + n);}

            const_reference at (size_type n) const{ 
                if (n >= _size)
                    throw std::out_of_range("ft::vector");
                // return &(_content + n);}
                return *(_content + n);}

            reference front(){ return *_content; }
            const_reference front() const{ return (*_content); }
            reference back() { return *(--end()); }
            const_reference back() const{ return *(--end()); }

            /* MODIFIERS */
            /* Assigns new contents to the vector, replacing its current contents, 
            and modifying its size accordingly. */
            template <class InputIterator>  
            void assign (InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL){
                size_t n = ft::distance(first, last);

                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_content + i);
                if (n > _capacity){
                    _alloc.deallocate(_content, _capacity);
                    _content = _alloc.allocate(n);
                    _capacity = n;
                }
                for (size_type i = 0; first != last; i++, first++){
                    _alloc.construct(_content + i, *first);
                }
                _size = n;
            }

            void assign (size_type n, const value_type& val){
                for(size_type i = 0; i < n; i++)
                    _alloc.destroy(_content + i);
                if (n > _capacity){
                    _alloc.deallocate(_content, _capacity);
                    _content = _alloc.allocate(n);
                    _capacity = n;
                }
                for(size_type i = 0; i < n; i++)
                    _alloc.construct(_content + i, val);
                _size = n;
            }

            /* Adds a new element at the end of the vector, after its current last element, may realloc */
            void push_back (const value_type& val){
                if (!_size)
                    reserve(1);
                else if ( _size + 1 > _capacity)
                    reserve(_size * 2);
                _alloc.construct(_content + _size, val);
                _size++;
            }

            void pop_back(){
                _size--;
                _alloc.destroy(_content + _size);
            }


            iterator insert (iterator position, const value_type& val){
                
                size_t n = ft::distance(begin(), position);

                if (!_size)
                {
                    _content = _alloc.allocate(1);
                    _alloc.construct(_content, val);
                    _capacity++;
                    _size++;
                    return _content;
                }
                else if ( _size + 1 > _capacity)
                {
                    reserve(_size * 2);
                }

                size_t reverseN = (_size - n);
                for(size_t m = 0; m < reverseN; m++)
                {
                    size_t pos = _size - m;
                    _alloc.destroy(_content + pos);
                    _alloc.construct(_content + pos, *(_content + pos - 1));
                }
                _alloc.destroy(_content + n);
                _alloc.construct(_content + n, val);
                _size++;
                return (_content + n);
            }

            void insert (iterator position, size_type n, const value_type& val){
                
                size_t x = ft::distance(begin(), position);
                size_t y = _size;

                if ( _size + n > _capacity )
                {
                    reserve((_size * 2) + n);
                }
                _size += n;

                size_t diff = y - x;
                for(size_t i = 0; i <= diff; i++, y--)
                {
                    size_t endPos = _size - i;
                    _alloc.destroy(_content + endPos);
                    _alloc.construct(_content + endPos, *(_content + y));
                }

                for(size_t i = x; i < (x + n); i++){
                    _alloc.destroy(_content + i);
                    _alloc.construct(_content + i, val);
                }
            }


            template <class InputIterator>    
            void insert (iterator position, InputIterator first, InputIterator last, 
            typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL){
                
                size_t x = ft::distance(begin(), position);
                size_t y = _size;
                size_t range = ft::distance(first,last) ;

                if ( _size + range > _capacity)
                {
                    reserve((_size * 2) + range);
                }
                _size += range; 

                size_t diff = y - x;
                for(size_t i = 0; i <= diff; i++, y--)
                {
                    size_t endPos = _size - i;
                    _alloc.destroy(_content + endPos);
                    _alloc.construct(_content + endPos, *(_content + y));
                }

                for(size_t i = x; i < (x + range); i++, first++){
                    _alloc.destroy(_content + i);
                    _alloc.construct(_content + i, *first);
                }
            }


            iterator erase (iterator position){
                size_t x = ft::distance(begin(), position);
                size_t diff = _size - x;
                size_t i = x;
                
                for (size_t j = 0; j < diff; i++, j++){
                    _alloc.destroy(_content + (i));
                    _alloc.construct(_content + (i), *(_content + i + 1));
                }
                if (diff != 0)
                    _size--;
                return (_content + x);
            }

            iterator erase (iterator first, iterator last){
                size_t x = ft::distance(first, last) ;
                size_t y = ft::distance(begin(), last);
                size_t z = ft::distance(begin(), first);
                size_t ret = ft::distance(begin(), first);

                if (x > ft::distance(begin(), end())){
                    for(; first != last; first++, x--)
                    {
                        _alloc.destroy(_content + x);
                        _size--;
                    }
                    return (end());
                }
     
                for(size_t i = 0; i <= x; i++, y++, z++)
                {
                    _alloc.destroy(_content + z);
                    _alloc.construct(_content + z, *(_content + y));
                }

                _size -= x;
                return (_content + ret);
            }

            void swap (vector& x){
                vector tmp(x);
                pointer ptrTmp = x._content;

                x._capacity = _capacity;
                x._size = _size;
                x._content = _content;

                _capacity = tmp._capacity;
                _size = tmp._size;
                _content = ptrTmp;
            }

            void clear(){               
                for(size_t i = 0; i < _size; i++){
                    _alloc.destroy(_content + i);
                }
                _size = 0;
            }

            /* ALLOCATOR */
            allocator_type get_allocator() const{ return _alloc;}
    };

    /* RELATIONAL OPERATORS */
    template <class T, class Alloc>  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return ( lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class T, class Alloc>  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return (!(lhs == rhs));
    }

    template <class T, class Alloc>  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class T, class Alloc>  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return (!(rhs < lhs));
    }

    template <class T, class Alloc>  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return (!(lhs <= rhs));
    }

    template <class T, class Alloc>  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
        return(!(lhs < rhs));
    }

    /* SWAP FUNCTION*/
    template <class T, class Alloc>  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
        x.swap(y);
    }

}
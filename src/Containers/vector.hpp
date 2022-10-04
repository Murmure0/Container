#pragma once

#include "../iterators/randomAccessIt.hpp"
#include "../iterators/itTraits.hpp"
#include "../iterators/reverseIt.hpp"
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
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(_content + i);
                _alloc.deallocate(_content, _capacity);

                _capacity = _size = x.size();
                _content = _alloc.allocate(_size);
                iterator first = x.begin();
                iterator end = x.end();
                for (size_t i = 0; first != end; first, i++)
                    _alloc.construct(_content + i, *first);
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
            void resize (size_type n, value_type val = value_type()){
                if (n < _size)
                {
                    for (size_type i = n; i < _size; i++)
                        _alloc.destroy(_content + i);
                    _size = n;
                }
                else if (n > _size)
                {
                    if (n > _capacity)
                        reserve(n);
                    else {
                        for (; n <_size ; n++){
                            if (val)
                                push_back(val);
                                _content + n = vector();
                        }
                    }
                }
            }


            size_type capacity() const{ return _capacity; };
            bool empty() const { return _size; }

            /* Requests that the vector capacity be at least enough to contain n elements. */
            void reserve (size_type n){
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
                else
                    return *(_content + n);}
            const_reference at (size_type n) const{ 
                if (n >= _size)
                    throw std::out_of_range("ft::vector");
                else
                    return &(_content + n);}

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
                }
                for(size_type i = 0; i < n; i++)
                    _alloc.construct(_content + i, val);
                _size = n;
            }

            /* Adds a new element at the end of the vector, after its current last element, may realloc */
            void push_back (const value_type& val){
                if ( _size + 1 > _capacity)
                    reserve(_size + 1);
                _alloc.construct(_content + _size, val);
                _size++;
            }

            void pop_back(){
                _size--;
                _alloc.destroy(_content + _size);
            }

            // Here : 
            iterator insert (iterator position, const value_type& val){
                
                size_t n = ft::distance(begin(), position);

                if ( _size + 1 > _capacity)
                {
                    reserve(_size + 1);
                    _size++;
                }
                else if (_size == 0)
                {
                    _alloc.allocate(1);
                    _alloc.construct(_content, val);
                    _size++;
                    return _content;
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
                return (_content + n);
            }

            void insert (iterator position, size_type n, const value_type& val){
                
                size_t x = ft::distance(begin(), position);
                size_t y = _size;

                if ( _size + n > _capacity )
                {
                    reserve(_size + n);
                    _size += n;
                }
                else if (_size == 0)
                {
                    _alloc.allocate(n);
                    for(;n > 0; n--){
                        _alloc.construct(_content +n, val);
                    }
                    _size = n;
                }
 
                size_t reverseN = x + n +1 ;
                // size_t contentToCopy = reverseN +n ; //méh
                // std::cout << "x ;" << x << std::endl;
                // std::cout << "n ;" << n << std::endl;
                // std::cout << "content (x+n-1) ;" << *(_content +n + x -1) << std::endl;
                
                // std::cout << "reverseN ;" << reverseN << std::endl;
                // std::cout << "contenttocopy ;" << contentToCopy << std::endl;
                for(size_t m = 0; m <= reverseN; m++, y--)
                {
                    size_t endPos = _size - m;
                    _alloc.destroy(_content + endPos);
                    _alloc.construct(_content + endPos, *(_content + y));
                }

                for(size_t i = x; i < (x + n); i++){
                    _alloc.destroy(_content + i);
                    _alloc.construct(_content + i, val);
                }
            }


            // template <class InputIterator>    
            // void insert (iterator position, InputIterator first, InputIterator last, 
            // typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL){
                
            // }


            iterator erase (iterator position);
            iterator erase (iterator first, iterator last);
            void swap (vector& x);
            void clear();

            /* ALLOCATOR */
            allocator_type get_allocator() const{ return _alloc;}
    };

    /* RELATIONAL OPERATORS */
    template <class T, class Alloc>  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>  bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

    /* SWAP */
    template <class T, class Alloc>  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

}
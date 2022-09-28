#pragma once

#include "../iterators/randomAccessIt.hpp"
#include "../iterators/itTraits.hpp"
#include "../iterators/reverseIt.hpp"
#include "../utils/type_traits.hpp"
#include <memory>




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
                if (n < 0)
                    throw std::out_of_range("ft::vector");
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
                _size = _capacity = std::distance(first, last);
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
            reverse_iterator rbegin(){ return (_content + _size); }
            const_reverse_iterator rbegin() const{ return (_content + _size); }
            reverse_iterator rend(){ return (_content + _size); }
            const_reverse_iterator rend() const{ return (_content + _size); }

            /* CAPACITY */
            size_type size() const{
                // const_iterator it = begin();
                // const_iterator ite = end();
                // size_type i = 0;
                // for (; it != ite; it++, i++)
                //     ;
                // return i;

                /* or */
                return _size; 
            }

            /* Returns the maximum number of elements, each of member type value_type (an alias of allocator's template parameter)
                that could potentially be allocated by a call to member allocate.
                A call to member allocate with the value returned by this function can still fail to allocate the requested storage. */    
            size_type max_size() const{
                return _alloc.max_size();
            }

            // void resize (size_type n, value_type val = value_type()){
            //     if (n < _size)
            //     {
                    
            //         _alloc.destroy(_content + n);
            //         _alloc.deallocate(_content + n, capacity);
            //         _size = _capacity = n;
            //     }
            //     else if (n > _size)
            //     {
            //         if (n > _capacity)
            //         {
            //            pointer tmp = _alloc.allocate(n);
            //            iterator it = begin();
            //            iterator ite = end();

            //         }
            //     }
            // }
            void resize (size_type n, value_type val = value_type());
            size_type capacity() const;
            bool empty() const;
            void reserve (size_type n);

            /* ELEMENT ACCESS */
            reference operator[] (size_type n);
            const_reference operator[] (size_type n) const;
            reference at (size_type n);
            const_reference at (size_type n) const;
            reference front();
            const_reference front() const;
            reference back();
            const_reference back() const;

            /* MODIFIERS */
            template <class InputIterator>  void assign (InputIterator first, InputIterator last);
            void assign (size_type n, const value_type& val);
            void push_back (const value_type& val);
            void pop_back();
            iterator insert (iterator position, const value_type& val);
            void insert (iterator position, size_type n, const value_type& val);
            template <class InputIterator>    void insert (iterator position, InputIterator first, InputIterator last);
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
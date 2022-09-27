#pragma once

#include "../iterators/randomAccessIt.hpp"
#include "../iterators/itTraits.hpp"
#include "../iterators/reverseIt.hpp"
#include <memory>
#include <iterator>



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
            /* enable_if : we want to write a template that only makes sense for some types, 
            we must make it fail deduction for invalid types right in the declaration, to cause substitution failure. 
            If the invalid type sneaks past the overload candidate selection phase, the program won't compile. */


            template <class InputIterator> 
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
            typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = NULL){
                _alloc = alloc;
                _size = _capacity = std::distance(first, last);
                _content = _alloc.allocate(_size);
                for(size_t i = 0; first != last; first++, i++)
                {
                    _alloc.construct(_content + i, *first);
                }
            }	
            // template <class InputIterator> 
            // vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()){
            //     _alloc = alloc;
            //     _size = _capacity = std::distance(first, last);
            //     _content = _alloc.allocate(_size);
            //     for(size_t i = 0; first != last; first++, i++)
            //     {
            //         _alloc.construct(_content + i, *first);
            //     }
            // }	

            /* copy constructor, constructs a container with a copy of each of the elements in x, in the same order. */
            vector (const vector& x){
                _capacity = _size = x.size();
                _alloc = x.get_allocator();
                _content = _alloc.allocate(_size);
                iterator first = x.begin();
                iterator end = x.end();
                for (size_t i = 0; first != end; first, i++)
                    _alloc.construct(_content + i, *first);
            }

            /* destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator. */
            ~vector(){
                _alloc.deallocate(_content, _capacity);
                _alloc.destroy(_content);
            }
            
            /* Copies all the elements from x into the container. */
            vector& operator= (const vector& x){
                _alloc.deallocate(_content, _capacity);
                _alloc.destroy(_content);

                _capacity = _size = x.size();
                _content = _alloc.allocate(_size);
                iterator first = x.begin();
                iterator end = x.end();
                for (size_t i = 0; first != end; first, i++)
                    _alloc.construct(_content + i, *first);
            }

            /* ITERATORS */
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;
            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            reverse_iterator rend();
            const_reverse_iterator rend() const;

            /* CAPACITY */
            size_type size() const;
            size_type max_size() const;
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
            allocator_type get_allocator() const;
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
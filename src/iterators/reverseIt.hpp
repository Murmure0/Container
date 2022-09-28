#pragma once

#include "itTraits.hpp"

namespace ft{

    template <class Iterator>
    class reverse_iterator
    {
        public:
                typedef typename iterator_traits<Iterator>::value_type         value_type;
                typedef typename iterator_traits<Iterator>::difference_type    difference_type;
                typedef typename iterator_traits<Iterator>::pointer            pointer;
                typedef typename iterator_traits<Iterator>::reference          reference;
                typedef typename iterator_traits<Iterator>::iterator_category  iterator_category;
                typedef Iterator                                                               iterator_type;

        private:
            Iterator _current;
        
        public:
        
        /*CONSTRUCTORS & DESTRUCTOR */
        reverse_iterator(): _current(){ return; }
        explicit reverse_iterator(iterator_type it) : _current(it._current){ return; }
        template <class U>  reverse_iterator (const reverse_iterator<U>& other) : _current(other.base()) { return; }
        ~reverse_iterator(){ return; }

        pointer base(){ 
            return _current; 
        }
        
        /* OPERATORS */
        reverse_iterator<Iterator>& operator=(const reverse_iterator<Iterator>& other) {
            _current = other.base();
            return *this;
        }

        operator reverse_iterator<const Iterator>() const{ return _current; }
            /* Accesses the pointed-to element : */

        reference operator*() const {
            Iterator tmp = _current;
            --tmp;
            return *tmp;
        }

        pointer   operator->() const { 
            return &(operator*());
        }

            /* Advances or decrements the iterator : */

        reverse_iterator& operator++(){
            --_current;
            return *this;
        }
        reverse_iterator  operator++(int){
            reverse_iterator tmp(*this);
            --_current;
            return tmp;
        }
        reverse_iterator& operator--(){
            ++_current;
            return *this;
        }
        reverse_iterator  operator--(int)
        {
            reverse_iterator tmp(*this);
            ++_current;
            return tmp;
        }
        reverse_iterator& operator+=(difference_type n){
            _current = _current - n;
            return *this;
        }
        reverse_iterator& operator-=(difference_type n){
            _current = _current + n;
            return *this;
        }
        reverse_iterator  operator+(difference_type n) const{
            return (reverse_iterator(_current - n));
        }
        reverse_iterator  operator-(difference_type n) const{
            return(reverse_iterator(_current + n));
        }
        reference         operator[](difference_type n) const{
            return (*(_current - n - 1));
        }
    };
    /* COMPARING OPERATORS */
    /* compares the underlying iterators */

    template <class Iterator1, class Iterator2>
    bool    operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
        return (x.base() == y.base());
    }

    template <class Iterator1, class Iterator2>
    bool    operator<(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
        return (x.base() < y.base());
    }

    template <class Iterator1, class Iterator2>
    bool    operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
        return (x.base() != y.base());
    }

    template <class Iterator1, class Iterator2>
    bool    operator>(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
        return (x.base() > y.base());
    }

    template <class Iterator1, class Iterator2>
    bool    operator>=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
        return (x.base() >= y.base());
    }

    template <class Iterator1, class Iterator2>
    bool    operator<=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y){
        return (x.base() <= y.base());
    }

    template <class Iterator>  
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& x,
            const reverse_iterator<Iterator>& y){
                return (y.base() - x.base());
            }


    template <class Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& x){
                return (x.base() - n);
            }
}
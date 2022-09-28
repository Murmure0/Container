#pragma once

#include "itTraits.hpp"

namespace ft{

    template<typename T>
    class random_access_iterator : ft::Iterator<ft::random_access_iterator_tag, T>
    {
        public:
                typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
                typedef  typename ft::Iterator<ft::random_access_iterator_tag, T>::difference_type      difference_type;
                typedef  typename ft::Iterator<ft::random_access_iterator_tag, T>::pointer              pointer;
                typedef  typename ft::Iterator<ft::random_access_iterator_tag, T>::reference            reference;
                typedef  typename ft::Iterator<ft::random_access_iterator_tag, T>::iterator_category    iterator_category;

        private:
            pointer _current;
        
        public:

        /* CONSTRUCTOR & DESTRUCTOR */
        random_access_iterator(): _current(NULL){ return; }
        random_access_iterator(random_access_iterator const &src) : _current(src._current){ return; }
        random_access_iterator(pointer ptr) : _current(ptr){ return; }
        ~random_access_iterator(){ return; }

        random_access_iterator& operator=(const random_access_iterator& t){
            _current = t._current;
            return (*this);
        }

        operator random_access_iterator<const T>() const{ return _current; }

        pointer base() const { return _current; }

        reference operator*() const { return *_current; }

        pointer   operator->() const { return _current; }


        /* INCREMENT/DECREMENT OPERATORS */

        random_access_iterator& operator++(){
            _current++; 
            return (*this);
        }

        random_access_iterator  operator++(int){
            random_access_iterator tmp(*this);
            _current++;
            return tmp;
        }

        random_access_iterator& operator--(){
            _current--;
            return (*this);
        }

        random_access_iterator  operator--(int){
            random_access_iterator tmp(*this);
            _current--;
            return tmp;
        }

        random_access_iterator  operator+(difference_type n) const { return (_current + n); }

        random_access_iterator& operator+=(difference_type n) { 
            _current += n;
            return (*this);
        }
        random_access_iterator  operator-(difference_type n) const { return (_current - n); }

        random_access_iterator& operator-=(difference_type n) {
            _current -= n;
            return (*this);
        }

        reference         operator[](difference_type n) const { return _current[n]; }
    };

    /* COMPARISON OPERATORS */

    template <typename Iterator1, typename Iterator2>
    bool    operator==(const ft::random_access_iterator<Iterator1>& x, const ft::random_access_iterator<Iterator2>& y)
    {
        return (x.base() == y.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool    operator!=(const ft::random_access_iterator<Iterator1>& x, const ft::random_access_iterator<Iterator2>& y)
    {
         return (!(x.base() == y.base()));
    }

    template <typename Iterator1, typename Iterator2>
    bool    operator<(const ft::random_access_iterator<Iterator1>& x, const ft::random_access_iterator<Iterator2>& y)
    {
        return (x.base() < y.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool    operator>(const ft::random_access_iterator<Iterator1>& x, const ft::random_access_iterator<Iterator2>& y)
    {
        return (!(x.base() < y.base()));
    }

    template <typename Iterator1, typename Iterator2>
    bool    operator>=(const ft::random_access_iterator<Iterator1>& x, const ft::random_access_iterator<Iterator2>& y)
    {
        return (x.base() >= y.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool    operator<=(const ft::random_access_iterator<Iterator1>& x, const ft::random_access_iterator<Iterator2>& y)
    {
        return (x.base() <= y.base());
    }

    template <typename Iterator>
    ft::random_access_iterator<Iterator> operator+(typename ft::random_access_iterator<Iterator>::difference_type n,
            const ft::random_access_iterator<Iterator>& x)
            {
                return (x + n);
            }

    template <typename Iterator1, typename Iterator2>
    typename ft::random_access_iterator<Iterator1>::difference_type
    operator-(const ft::random_access_iterator<Iterator1>& x, const ft::random_access_iterator<Iterator2>& y)
    {
        return (x.base() - y.base());
    }
}
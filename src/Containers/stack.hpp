#pragma once

#include "vector.hpp"

namespace ft{

    template < class T, class Container = ft::vector<T> > 
    class stack
    {
        public :

            typedef Container                                   container_type;
            typedef typename container_type::value_type         value_type;
            typedef typename container_type::reference          reference;
            typedef typename container_type::const_reference    const_reference;
            typedef typename container_type::size_type          size_type;

        protected :
        
            container_type c;

        public:

            explicit stack (const container_type& ctnr = container_type()): c(ctnr) {}

            bool empty() const {
                return (c.empty()); }

            size_type size() const{
                return (c.size()); }

            value_type& top(){
                return (c.back()); }

            const value_type& top() const{
                return (c.back()); }

            void push (const value_type& val){
                c.push_back(val); }

            void pop(){
                c.pop_back(); }


            template <class Type, class Cont>  
            friend bool operator== (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs);
            
            template <class Type, class Cont>  
            friend bool operator<  (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs);
    };

        template <class Type, class Cont>  
        bool operator== (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs){
            return (lhs.c == rhs.c); }
            
        template <class Type, class Cont>  
         bool operator<  (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs){
            return (lhs.c < rhs.c); }

        template <class Type, class Cont>  
        bool operator!= (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs){
            return (!(lhs == rhs)); }

        template <class Type, class Cont>  
        bool operator<= (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs){
            return (!(rhs < lhs)); }

        template <class Type, class Cont>  
        bool operator>  (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs){
            return (!(lhs <= rhs)); }

        template <class Type, class Cont>  
        bool operator>= (const stack<Type,Cont>& lhs, const stack<Type,Cont>& rhs){
            return(!(lhs < rhs)); }
}
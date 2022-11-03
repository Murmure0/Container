#pragma once

namespace ft{

    template <class Arg1, class Arg2, class Result>
    struct binary_function {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
  };

    template <class T> 
    struct less : binary_function <T,T,bool> {
    bool operator() (const T& x, const T& y) const 
    {return (x < y); } 
    };
}

/*
    node *node1;
    node *node2;

    if I write this : *node1 < *node2
    it means this : value_compare(node1->content, node2->content)
    or this : key_compare(node1->content.first, node2->content.first)
    beacause I did an operator overload in my RBNode
*/
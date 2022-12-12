/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redBlackNode.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:24:21 by mberthet          #+#    #+#             */
/*   Updated: 2022/11/22 15:15:44 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "redBlackTree.hpp"

namespace ft
{
    template <class T, class Compare, class Alloc>
    class BsT;
    
    template <class T, class Compare, class Alloc >
    class BsT<T, Compare, Alloc>::node
    {

        public:

            const value_compare &comp;
            T       pair;
            node*   parent;
            node*   leftC;
            node*   rightC;
            node*   end; //if the node is already the end, this will be the root
            bool    col;

            explicit node(node* e, const value_compare& comp = value_compare()) : comp(comp), pair(), end(e) {
                parent = NULL;
                leftC = NULL;
                rightC = NULL;
                col = BLACK;
            }

            node(node* e, T p, const value_compare& comp = value_compare()) : comp(comp), pair(p), end(e) {
                parent = NULL;
                leftC = NULL;
                rightC = NULL;
                col = BLACK;
            }

            node(node* e,T p, node*par, node*lC, node*rC, const value_compare& comp = value_compare())
                : comp(comp), pair(p), parent(par), leftC(lC), rightC(rC), end(e) {
                col = BLACK;
            }

            ~node() {
            }


            operator				typename BsT<const T, Compare, Alloc>::node() const
            {
                return BsT<const T, Compare, Alloc>::node(*this);
            }

            node(node const &src) : comp(src.comp), pair(src.pair), parent(src.parent), leftC(src.leftC), rightC(src.rightC), end(src.end), col(src.col) {}

            node* getEnd(){
                return this->end;
            }

            node &operator=(node const &rhs){

                parent = rhs.parent; 
                leftC = rhs.leftC; 
                rightC = rhs.rightC; 
                col = rhs.col;
                end = rhs.end;
                return *this;
            }

            node *findMin(){
                node *tmp = this;

                while (tmp->leftC && tmp->leftC != end){
                    tmp = tmp->leftC;
                }
                return tmp;
            }

            node* findMax(){
                node *tmp = this;
                
                while (tmp->rightC && tmp->rightC != end){
                    tmp = tmp->rightC;
                }
                return tmp;
            }

            node* findNext(){
                node* tmp = this;

                //s'il y a une branche a droite, on cherche la plus petite valeur
                if (tmp->rightC && tmp->rightC != end){
                    tmp = tmp->rightC;
                    return (tmp->findMin());
                }
                //sinon on remonte dans le parent 
                else if (tmp->parent){
                    while (tmp->parent && comp(tmp->parent->pair, tmp->pair)){
                        tmp = tmp->parent;
                    }
                    if( tmp->parent ){
                        return tmp->parent;
                    }
                }
                return end;
            }

            node* findPrevious(){
                node* tmp = this;

                if (!tmp->parent && !tmp->leftC && !tmp->rightC)
                    return tmp->end->findMax();
                else if (tmp->leftC != end){
                    tmp = tmp->leftC;
                    return tmp->findMax();
                }
                else {
                    while(tmp->parent && comp(tmp->pair, tmp->parent->pair))
                        tmp = tmp->parent;
                    return tmp->parent;
                }
                return end;
            }
    };
}
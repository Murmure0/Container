#pragma once
#include <iostream>
#define RED 1
#define BLACK 0

namespace ft{

    template <class T>
    class rdb {
        private:

            class node{
                public:
                T pair;
                node *parent;
                node *leftC;
                node *rightC;
                bool col;

                node(){
                    pair = T();
                    parent = NULL;
                    leftC = NULL;
                    rightC = NULL;
                    col = 0;
                }

                node(T p) : pair(p) {
                    parent = NULL;
                    leftC = NULL;
                    rightC = NULL;
                    col = 0;
                }

                node(T p, node*par, node*lC, node*rC) : pair(p), parent(par), leftC(lC), rightC(rC) {
                    col = 0;
                }

                ~node() {}

                node(node const &src) {
                    *this = src;
                }

                node &operator=(node const &rhs){
                    pair = rhs.pair;
                    parent = rhs.parent; 
                    leftC = rhs.leftC; 
                    rightC = rhs.rightC; 
                    col = rhs.col;
                    return *this;
                }
            };

            node *root;
            node *nullNode;


        public:
            ~rdb() {
                //should clean the content of the tree
            }

            rdb() {
                root = NULL;
            }

            rdb(T p) {
               
                root = new node(p);
                nullNode = new node;
                std::cout << "Content root first : " << root->pair.first  << " second : " << root->pair.second << " color : " << root->col << std::endl;
            }

            void setNodeNull(node *n, node *parent){
                n->col = 0;
                n->leftC = NULL;
                n->rightC = NULL;
                n->parent = parent;
                n->pair = T();
            }  

            T insertNode(T p){
                node *tmp = root;
                node *tmp2 = NULL;
                while (tmp){
                    if (p.first == tmp->pair.first)
                        return T(tmp->pair.first, 0);
                    tmp2 = compare(p, tmp);
                    if (tmp2 == tmp)
                        break;
                    else 
                        tmp = tmp2;
                }
                if (p.first < tmp->pair.first)
                    (tmp->leftC) = new node(p, tmp, NULL, NULL);
                else
                    (tmp->rightC) = new node(p, tmp, NULL, NULL);
                return p;
            }         

            node *compare(T p, node *n){
                if (p.first < n->pair.first && n->leftC)
                    return (n->leftC);
                else if(p.first > n->pair.first && n->rightC)
                    return (n->rightC);
                else
                    return n;
            }

            node *findMin(){
                node *tmp = root;
                while (tmp->leftC != NULL){
                    tmp = tmp->leftC;
                    //std::cout << tmp->pair.first << std::endl;
                }
                return tmp;
            }

            node *findMin(node *n){
                node *tmp = n;
                while (tmp->leftC != NULL){
                    tmp = tmp->leftC;
                }
                return tmp;
            }

            node* findNext(node *n){
                node* tmp = n;
                //s'il y a une branche a droite, on cherche la plus petite valeur
                if (tmp->rightC){
                    tmp = tmp->rightC;
                    return (findMin(tmp));
                }
                //sinon on remonte dans le parent 
                else if (tmp->parent){
                    while (tmp->parent && tmp->parent->pair.first < tmp->pair.first){
                        tmp = tmp->parent;
                    }
                    if(tmp->parent ){
                        return tmp->parent;
                    }
                }
                return NULL;
            }

            void printTree(){
                // node* tmp = findMin();
                // while (tmp)
                // {
                //     std::cout << tmp->pair.first;
                //     tmp = findNext(tmp);
                // }
                node* tmp = root;
                std::cout << "root : " << tmp->pair.first << std::endl;

            }
    };
}
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

                node(T p){
                    pair = p;
                    parent = NULL;
                    leftC = NULL;
                    rightC = NULL;
                    col = 0;
                }

                node(T p, node*par){
                    pair = p;
                    parent = par;
                    leftC = NULL;
                    rightC = NULL;
                    col = 0;
                }

                ~node() {}

                node(node const&src){
                    pair = src.pair;
                    parent = src.parent; 
                    leftC = src.leftC; 
                    rightC = src.rightC; 
                    col = src.col;
                }
                node operator=(node const&rhs){
                    *this = rhs;
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
                *root = node(p);
                std::cout << "Content root first : " << root->pair.first  << " second : " << root->pair.second << " color : " << root->col << std::endl;
            }

            void setNodeNull(node *n, node *parent){
                n->col = 0;
                n->leftC = NULL;
                n->rightC = NULL;
                n->parent = parent;
                n->pair = T();
            }        
    };
}
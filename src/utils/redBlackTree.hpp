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
                //should clean the content of the tree, yep it should
                //but it didn't for now
                //bc i'm enjoying creating this beautiful tree.
                //Feeling inspired, may clean later.
                /*The constructor create an empty tree by initializing root to NULL value. 
                Function Destroy() is implemented recursively whereby the function will destroy all nodes 
                in the left subtree first, followed by destroying nodes in the right subtree. 
                Lastly, the root node will be destroyed.*/
            }

            rdb() {
                root = NULL;
            }

            rdb(T p) {
               
                root = new node(p);
                nullNode = new node;
                std::cout << "Content root first : " << root->pair.first  << " second : " << root->pair.second << " color : " << root->col << std::endl;
            }

            node* getRoot(){
                return root;
            }

            void setNodeNull(node *n, node *parent){
                n->col = 0;
                n->leftC = NULL;
                n->rightC = NULL;
                n->parent = parent;
                n->pair = T();
            }  

            node *compare(T p, node *n){
                if (p.first < n->pair.first && n->leftC)
                    return (n->leftC);
                else if(p.first > n->pair.first && n->rightC)
                    return (n->rightC);
                else
                    return n;
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

            void deleteNode(T p){
                node* toDelete = findNode(p);
                //node is root and have no child // OK
                // if (toDelete == root && !toDelete->leftC && !toDelete->rightC){
                //     std::cout << "ROOT todelete : "<<toDelete->pair.first << " has been removed from the tree"<< std::endl;
                //     delete toDelete;
                //     root = new node();
                //     return;
                // }
                //node is a leaf //OK
                if (!toDelete->leftC && !toDelete->rightC){ //on supprime une feuille
                    if (toDelete->parent)
                        toDelete->parent->leftC ? toDelete->parent->leftC = NULL : toDelete->parent->rightC = NULL;


                    // if (toDelete->parent->leftC == toDelete && toDelete->parent)
                    //     toDelete->parent->leftC = NULL;
                    // else if (toDelete->parent->rightC == toDelete && toDelete->parent)
                    //     toDelete->parent->rightC = NULL;
                    delete toDelete;
                }

                // toDelete has one child
                /*
                bool isLeftChild = (toDelete->parent->leftC == toDelete ? true : false);
                if (has one child)
                {
                    bool hasLeftChild = (toDelete->leftC ? true : false); //does toDelete have a LeftChild?
                    if (!toDelete->parent)
                        hasLeftChild ? root = left : root = right;
                    else if (isLeftChild)
                        hasLeftChild ? toDelete->parent->leftC = toDelete->leftC : toDelete->parent->leftC = toDelete->rightC;
                    else
                        hasLeftChild ? toDelete->parent->rightC = toDelete->leftC : toDelete->parent->rightC = toDelete->rightC;
                    hasLeftChild ? toDelete->leftC->parent = toDelete->parent : toDelete->rightC->parent = toDelete->parent;
                    delete toDelete;
                }

                else if (has two children)
                {
                    node *replacer = smallest(toDelete->right);
                    node *copy = new node(replacer->pair, toDelete->parent, toDelete->left, toDelete->right);

                    if (!toDelete->parent)
                        root = copy;
                    else
                        isLeftChild ? toDelete->parent->left = copy :  toDelete->parent->right = copy;
                    toDelete->leftC->parent = copy;
                    toDelete->rightC->parent = copy;
                    delete toDelete;
                    this->deleteNode(replacer); //must be done depending on pointer
                }
                */

                else if (toDelete->leftC && !toDelete->rightC) { // toDelete has a left child: //OK
                    if (toDelete->parent){ //toDelete is not root :
                        toDelete->leftC->parent = toDelete->parent;
                        if (toDelete->parent->leftC == toDelete){ //toDelete on its parent left  //OK
                            toDelete->parent->leftC = toDelete->leftC;
                            // toDelete->leftC->parent = toDelete->parent;
                        }
                        else if (toDelete->parent->rightC == toDelete){ //toDelete is on its parent right //OK
                            toDelete->parent->rightC = toDelete->leftC;
                            // toDelete->leftC->parent = toDelete->parent;
                        }
                    }
                    else{ //delete is root //OK
                        root = toDelete->leftC;
                        toDelete->leftC->parent = NULL;
                    }

                    delete toDelete; 
                }

                else if (!toDelete->leftC && toDelete->rightC){// toDelete has a right child: //OK
                    if (toDelete->parent){ //toDelete is not root :
                        toDelete->rightC->parent = toDelete->parent;
                        if (toDelete->parent->leftC == toDelete){ //toDelete on its parent left //OK
                            toDelete->parent->leftC = toDelete->rightC;
                            // toDelete->rightC->parent = toDelete->parent;
                        }
                        else if (toDelete->parent->rightC == toDelete){ //toDelete on its parent right //OK
                            toDelete->parent->rightC = toDelete->rightC;
                            // toDelete->rightC->parent = toDelete->parent;
                        }
                    }
                    else{ //delete is root //OK
                        root = toDelete->rightC;
                        toDelete->rightC->parent = NULL;
                    }

                    delete toDelete; 
                }

                //DO A FUCKING FONCTION TO REATTRIBUTE PTR

                //node have two child 
                else if (toDelete->leftC && toDelete->rightC) 
                { 
                    if (toDelete->parent){ //toDelete is not root 

                        node *nextDl = findNext(toDelete);

                        if (toDelete->parent->leftC == toDelete){ //node to delete is at left of its parent //OK

                            if(!nextDl->rightC){ //next node : no child , no need to check left //OK

                                if(nextDl == nextDl->parent->leftC)
                                    nextDl->parent->leftC = NULL;
                                else if (nextDl == nextDl->parent->rightC)
                                    nextDl->parent->rightC = NULL;
                                
                                toDelete->parent->leftC = nextDl; //links w/ parent 
                                nextDl->parent = toDelete->parent;

                                nextDl->leftC = toDelete->leftC; // links w/leftChild
                                toDelete->leftC->parent = nextDl;

                                nextDl->rightC = toDelete->rightC; //links w/rightChild
                            }
                            else if(nextDl->rightC && toDelete == nextDl->parent){ //next node has rightChild and to delete is the direct parent //OK
                                nextDl->parent = toDelete->parent; //links w/ parent
                                toDelete->parent->leftC = nextDl;

                                nextDl->leftC = toDelete->leftC; //links w/leftChild
                                toDelete->leftC->parent = nextDl;
                            }
                            else if(nextDl->rightC && toDelete != nextDl->parent){ //next node has rightChild and to delete is NOT the direct parent //OK
                                nextDl->parent->leftC = nextDl->rightC; // links w/ Next right child
                                nextDl->rightC->parent = nextDl->parent;   

                                nextDl->parent = toDelete->parent; //links w/ parent
                                toDelete->parent->leftC = nextDl;

                                nextDl->leftC = toDelete->leftC; //links w/leftChild
                                toDelete->leftC->parent = nextDl;

                                nextDl->rightC = toDelete->rightC; //links w/rightChild
                                toDelete->rightC->parent = nextDl;
                            }
                        }

                        else if (toDelete->parent->rightC == toDelete){ //node to delete is at right of its parent //OK

                            if(!nextDl->rightC){ //next node : no child //OK
                                
                                if(nextDl == nextDl->parent->leftC)
                                    nextDl->parent->leftC = NULL;
                                else if (nextDl == nextDl->parent->rightC)
                                    nextDl->parent->rightC = NULL; //pffff marche differement si a droite ou a gauche de root 

                                nextDl->parent = toDelete->parent; //links w/ parent
                                toDelete->parent->rightC = nextDl; 

                                nextDl->leftC = toDelete->leftC; // links w/leftChild
                                toDelete->leftC->parent = nextDl;
                                
                                nextDl->rightC = toDelete->rightC;
                                toDelete->rightC->parent = nextDl;
                                std::cout << "todelete : "<<toDelete->pair.first << " has been removed from the tree " << nextDl->pair.first << std::endl;
                            }
                            else if(nextDl->rightC && toDelete == nextDl->parent){ // next node has right child and to delete is the direct parent //OK

                                nextDl->parent = toDelete->parent;
                                toDelete->parent->rightC = nextDl;

                                nextDl->leftC = toDelete->leftC;
                                toDelete->leftC->parent = nextDl;
                            }
                            else if (nextDl->rightC && toDelete != nextDl->parent){ // next node has rightChild and to delete is NOT the direct parent //OK
                                nextDl->rightC->parent = toDelete->rightC;
                                toDelete->rightC->leftC = nextDl->rightC;

                                nextDl->parent = toDelete->parent;
                                toDelete->parent->rightC = nextDl;

                                nextDl->leftC = toDelete->leftC;
                                toDelete->leftC->parent = nextDl;

                                nextDl->rightC = toDelete->rightC;
                                toDelete->rightC->parent = nextDl;
                            }
                        }
                    }
                    else if (toDelete == root){ // toDelete is root and has 2child //
                        node *nextDl = findNext(toDelete);
                            nextDl->parent = NULL;

                            nextDl->leftC = toDelete->leftC;
                            toDelete->leftC->parent = nextDl;

                        if (toDelete->rightC != nextDl){ // nextdl isn't direct toD's right //Okay
                            if (nextDl->rightC){ // and have a right child
                                toDelete->rightC->leftC = nextDl->rightC;
                                nextDl->rightC->parent = toDelete->leftC;
                            }
                            else if (!nextDl->rightC){ // and doesn't have a right child //Okay
                                toDelete->rightC->leftC = NULL;
                            }
                            nextDl->rightC = toDelete->rightC;
                            toDelete->rightC->parent = nextDl;
                        }
                        root = nextDl;
                    }
                    delete toDelete; 
                }
            }

            node* findNode(T p){
                node *findMe= new node(p);
            
                node *treeNode = root;

                while(findMe->pair.first != treeNode->pair.first){
                    if (findMe->pair.first > treeNode->pair.first)   
                        treeNode = findNext(treeNode);
                    if (findMe->pair.first < treeNode->pair.first)   
                        treeNode = findPrevious(treeNode);
                }
                delete findMe;

                return treeNode;
            }

            node *findMin(){
                node *tmp = root;
                while (tmp->leftC != NULL){
                    tmp = tmp->leftC;
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

            node* findMax(){
                node *tmp = root;
                if (tmp->rightC){
                    while (tmp->rightC){
                        tmp = tmp->rightC;
                    }
                }
                return tmp;
            }

            node* findMax(node *n){
                node *tmp = n;
                //on recherche le parent avec la key la plus elevée
                if (tmp->parent){
                    while (tmp->parent && tmp->parent->pair.first > tmp->pair.first){
                        tmp = tmp->parent;
                    }
                }
                //on descend toute la branche droite
                if (tmp->rightC){
                    while (tmp->rightC){
                        tmp = tmp->rightC;
                    }
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

            node* findPrevious(node *n){
                node* tmp = n;
                if (tmp->leftC){
                    return tmp->leftC;
                }
                else if (tmp->parent){
                    while(tmp->parent && tmp->parent->pair.first > tmp->pair.first)
                        tmp = tmp->parent;
                    return tmp->parent;
                }
                return NULL;
            }


            void printBT(const std::string& prefix, const node* n, bool isLeft)
            {
                if( n != NULL )
                {
                    std::cout << prefix;

                    std::cout << (isLeft ? "├──" : "└──" );

                    // print the value of the n
                    std::cout << n->pair.first << std::endl;

                    // enter the next tree level - left and right branch
                    printBT( prefix + (isLeft ? "│   " : "    "), n->leftC, true);
                    printBT( prefix + (isLeft ? "│   " : "    "), n->rightC, false);
                }
                // else
                //     std::cout << "tree is empty" << std::endl;
            }

            void printBT(const node* n)
            {
                printBT("", n, false);
            }


    };
}
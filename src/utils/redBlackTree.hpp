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
                deleteNode(toDelete);}

            void deleteNode(node* toDelete){

                if (!toDelete->leftC && !toDelete->rightC){ // No Child
                    if (toDelete->parent)
                        toDelete->parent->leftC ? toDelete->parent->leftC = NULL : toDelete->parent->rightC = NULL;
                    else
                        root = NULL;
                    delete toDelete;
                }

                bool isLeftChild = (toDelete->parent->leftC == toDelete ? true : false); //toDelete is a left Child
                //One Child

                if ((toDelete->rightC && !toDelete->leftC) || (!toDelete->rightC && toDelete->leftC)){
                    bool hasLeftChild = (toDelete->leftC ? true : false); // toDelete has a left child
                    
                    if (toDelete == root)
                        hasLeftChild ? root = toDelete->leftC : root = toDelete->rightC;
                    else if (isLeftChild)
                        hasLeftChild ? toDelete->parent->leftC = toDelete->leftC : toDelete->parent->leftC = toDelete->rightC;
                    else
                        hasLeftChild ? toDelete->parent->rightC = toDelete->leftC : toDelete->parent->rightC = toDelete->rightC;
                    hasLeftChild ? toDelete->leftC->parent = toDelete->parent : toDelete->rightC->parent = toDelete->parent;
                    delete toDelete;
                }
                //Two Child

                else if (toDelete->leftC && toDelete->rightC){
                    node *prevToDelete = findPrevious(toDelete);
                    node *substitute = new node(prevToDelete->pair, toDelete->parent, toDelete->leftC, toDelete->rightC);

                    if (toDelete == root)
                        root = substitute;
                    else
                        isLeftChild ? toDelete->parent->leftC = substitute : toDelete->parent->rightC = substitute;
                    toDelete->leftC->parent = substitute;
                    toDelete->rightC->parent = substitute;
                    delete toDelete;
                    deleteNode(prevToDelete);
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
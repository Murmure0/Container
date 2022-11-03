#pragma once
#include <iostream>
#define RED 1
#define BLACK 0

namespace ft{

    template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
    class BsT {
        private:

            class node{

                public:

                    T       pair;
                    node    *parent;
                    node    *leftC;
                    node    *rightC;
                    bool    col;

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

                    ~node() {
                    }

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
                
                    operator			node<const T, Compare>() const;
                    bool				operator==(node const &right) const;
                    bool				operator!=(node const &right) const;
                    bool				operator<(node const &right) const;
                    bool				operator>(node const &right) const;
                    bool				operator<=(node const &right) const;
                    bool				operator>=(node const &right) const;
            };

            // var privee de tree :

            node *root; //manque le _
            node *nullNode; //used ?
            const Compare _comp;


        public:
            ~BsT() {
                node* tmp = findMin();
                node* toDel = tmp;
                while (tmp){
                    tmp = findNext(tmp);
                    deleteNode(toDel);
                    this->printBT(this->getRoot());
                    toDel = tmp;
                }
            }

            BsT() {
                root = NULL;
            }

            BsT(T p) {
               
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

                bool isLeftChild = false;
                if (toDelete->parent)
                    isLeftChild = (toDelete->parent->leftC == toDelete); //toDelete is a left Child

                if (!toDelete->leftC && !toDelete->rightC){ // No Child
                    if (toDelete->parent)
                        isLeftChild ? toDelete->parent->leftC = NULL : toDelete->parent->rightC = NULL;
                    else
                        root = NULL;
                    delete toDelete;
                }

                //One Child

                if ((toDelete->rightC && !toDelete->leftC) || (!toDelete->rightC && toDelete->leftC)){

                    bool hasLeftChild = (toDelete->leftC ? true : false); // toDelete has a left child
                    
                    if (toDelete == root){
                        hasLeftChild ? root = toDelete->leftC : root = toDelete->rightC;

                    }
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
                if (root == NULL){
                    return NULL;
                }
                node *tmp = root;
                while (tmp->leftC != NULL){
                    tmp = tmp->leftC;
                }
                return tmp;
            }

            node *findMin(node *n){
                if (root == NULL){
                    return NULL;
                }
                node *tmp = n;
                while (tmp->leftC != NULL){
                    tmp = tmp->leftC;
                }
                return tmp;
            }

            node* findMax(){
                if (root == NULL){
                    return NULL;
                }
                node *tmp = root;
                if (tmp->rightC){
                    while (tmp->rightC){
                        tmp = tmp->rightC;
                    }
                }
                return tmp;
            }

            node* findMax(node *n){
                if (root == NULL){
                    return NULL;
                }
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
#pragma once
#include <iostream>
#define RED 1
#define BLACK 0
#include "binary_function.hpp"
#include "../iterators/treeIterator.hpp"


namespace ft{

    template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
    class BsT {


        public:

            typedef Compare             value_compare;
        

            class node {

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

                    node *findMin(){
                        node *tmp = this;

                        while (tmp->leftC != NULL){
                            tmp = tmp->leftC;
                        }
                        return tmp;
                    }

                    node* findMax(){
                        node *tmp = this;
                        
                        while (tmp->rightC){
                            tmp = tmp->rightC;
                        }
                        return tmp;
                    }

                    node* findNext(){
                        node* tmp = this;
                        //s'il y a une branche a droite, on cherche la plus petite valeur
                        if (tmp->rightC){
                            tmp = tmp->rightC;
                            return (tmp->findMin());
                        }
                        //sinon on remonte dans le parent 
                        else {
                            while (tmp->parent && _comp(tmp->parent->pair, tmp->pair)){
                                tmp = tmp->parent;
                            }
                            if( tmp->parent ){

                                return tmp->parent;
                            }
                        }
                        return NULL;
                    }

                    node* findPrevious(){

                        //qd on est sur le node end ca va cracher, bisou, faudra renvoyer root.findmax()

                        node* tmp = this;
                        if (tmp->leftC){
                            tmp = tmp->leftC;
                            return tmp->findMax();
                        }
                        else {
                            while(tmp->parent && _comp(tmp->pair, tmp->parent->pair))
                                tmp = tmp->parent;
                            return tmp->parent;
                        }
                        return NULL;
                    }
            };

            typedef node          node_type;
            typedef typename Alloc::template rebind<node_type>::other allocator_type;

        private:


            // var privee de tree :

            node *root; //manque le _
            node *nullNode; //used ?
            static Compare _comp;
            // const static end   _end;
            //
            allocator_type _alloc;

        public:

            ~BsT() {
                node* tmp = findMin();
                node* toDel = tmp;
                while (tmp){
                    tmp = findNext(tmp);
                    deleteNode(toDel);
                    toDel = tmp;
                }
            }

            BsT() {
                root = NULL;
            }

            BsT(T p) {
               
                root = _alloc.allocate(1);
                _alloc.construct(root, node_type(p));
                nullNode = _alloc.allocate(1);
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
                if (_comp(p, n->pair) && n->leftC)
                    return (n->leftC);
                else if(_comp(n->pair, p) && n->rightC)
                    return (n->rightC);
                else
                    return n;
            }

            T insertNode(T p){
                node *tmp = root;
                node *tmp2 = NULL;
                
                if (!tmp){
                    root = _alloc.allocate(1);
                    _alloc.construct(root, node_type(p));
                }
                while (tmp){
                    if (!_comp(p,tmp->pair) && !_comp(tmp->pair, p))
                        return T(tmp->pair.first, 0);
                    tmp2 = compare(p, tmp);
                    if (tmp2 == tmp)
                        break;
                    else 
                        tmp = tmp2;
                }
                if (_comp(p, tmp->pair)){
                    (tmp->leftC) = _alloc.allocate(1);
                    _alloc.construct((tmp->leftC), node_type(p, tmp, NULL, NULL));
                }
                else{
                    (tmp->rightC) = _alloc.allocate(1);
                    _alloc.construct((tmp->rightC), node_type(p, tmp, NULL, NULL));
                }
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
                    _alloc.destroy(toDelete);
                    _alloc.deallocate(toDelete, 1);
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
                    _alloc.destroy(toDelete);
                    _alloc.deallocate(toDelete, 1);
                }
                //Two Child

                else if (toDelete->leftC && toDelete->rightC){

                    node *prevToDelete = findPrevious(toDelete);
                    //node *substitute = new node(prevToDelete->pair, toDelete->parent, toDelete->leftC, toDelete->rightC);

                    node *substitute = _alloc.allocate(1);
                    _alloc.construct(substitute, node_type(prevToDelete->pair, toDelete->parent, toDelete->leftC, toDelete->rightC));

                    if (toDelete == root)
                        root = substitute;
                    else
                        isLeftChild ? toDelete->parent->leftC = substitute : toDelete->parent->rightC = substitute;
                    toDelete->leftC->parent = substitute;
                    toDelete->rightC->parent = substitute;
                    _alloc.destroy(toDelete);
                    _alloc.deallocate(toDelete, 1);
                    deleteNode(prevToDelete);
                }
            }

            node* findNode(T p){
                node *findMe= _alloc.allocate(1);
                _alloc.construct(findMe, node_type(p));
            
                node *treeNode = root;

                while(_comp(findMe->pair,treeNode->pair) || _comp(treeNode->pair,findMe->pair)){ 
                    if (!_comp(findMe->pair, treeNode->pair))   
                        treeNode = findNext(treeNode);
                    if (_comp(findMe->pair, treeNode->pair))   
                        treeNode = findPrevious(treeNode);
                }
                _alloc.destroy(findMe);
                _alloc.deallocate(findMe, 1);
                return treeNode;
            }

            node *findMin(){ 
                if (root == NULL){
                    return NULL;
                }
                return root->findMin();
            }

            node *findMin(node *n){
               return n->findMin();
            }

            node* findMax(){
                if (root == NULL){
                    return NULL;
                }
                return root->findMax();
            }

            node* findMax(node *n){ 
                return n->findMax();
            }

            node* findNext(node *n){
                return n->findNext();
            }

            node* findPrevious(node *n){
                return n->findPrevious();
            }


            treeIterator<T, Compare> begin(){
                return treeIterator<T, Compare>(findMin());
            }

            treeIterator<T, Compare> end(){
                return treeIterator<T, Compare>(findMin());
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

    template <class T, class Compare, class Alloc>
    typename BsT<T, Compare, Alloc>::value_compare BsT<T, Compare, Alloc>::_comp = BsT<T, Compare, Alloc>::value_compare();

}
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

                    node() : pair(){
                        pair = T();
                        parent = NULL;
                        leftC = NULL;
                        rightC = NULL;
                        col = 1;
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

                    node *findMin(node *end){
                        node *tmp = this;

                        while (tmp->leftC && tmp->leftC != end){
                            tmp = tmp->leftC;
                        }
                        return tmp;
                    }

                    node* findMax(node *end){
                        node *tmp = this;
                        
                        while (tmp->rightC && tmp->rightC != end){
                            tmp = tmp->rightC;
                        }
                        return tmp;
                    }

                    node* findNext(node *end){
                        node* tmp = this;

                        //s'il y a une branche a droite, on cherche la plus petite valeur
                        if (tmp->rightC && tmp->rightC != end){
                            tmp = tmp->rightC;
                            return (tmp->findMin(end));
                        }
                        //sinon on remonte dans le parent 
                        else if (tmp->parent){
                            while (tmp->parent && _comp(tmp->parent->pair, tmp->pair)){
                                tmp = tmp->parent;
                            }
                            if( tmp->parent ){
                                return tmp->parent;
                            }
                        }
                        return end;
                    }

                    node* findPrevious(node *end){

                        //qd on est sur le node end ca va cracher, bisou, faudra renvoyer root.findmax()

                        node* tmp = this;
                        if (tmp->leftC){
                            tmp = tmp->leftC;
                            return tmp->findMax(end);
                        }
                        else {
                            while(tmp->parent && _comp(tmp->pair, tmp->parent->pair))
                                tmp = tmp->parent;
                            return tmp->parent;
                        }
                        return end;
                    }
            };

            typedef node          node_type;
            typedef typename Alloc::template rebind<node_type>::other allocator_type;

        private:


            // var privee de tree :

            node *root; //manque le _
            node *_end;
            static Compare _comp;
            allocator_type _alloc;
            size_t         _size;

        public:

            ~BsT() {
                node* tmp = findMin();
                node* toDel = tmp;
                while (tmp != _end){
                    tmp = findNext(tmp);
                    deleteNode(toDel);
                    toDel = tmp;
                }
                printBT(root);
                _alloc.destroy(_end);
                _alloc.deallocate(_end, 1);
            }

            BsT() {
                _end = _alloc.allocate(1);
                _alloc.construct(_end, node_type());
                root = _end;
                _size = 0;
            }

            BsT(T p) {
                root = _alloc.allocate(1);
                _alloc.construct(root, node_type(p));
                _end = _alloc.allocate(1);
                _alloc.construct(_end, node_type());
                setEndAfter(root);
                _size = 1;
            }

            BsT &operator=(BsT const &rhs){
                root = rhs.root;
                _end = rhs._end; 
                _size = rhs._size;
                return *this;
            }

            node* getRoot(){
                return root;
            }

            size_t getSize(){
                return _size;
            }

            void setEndAfter(node *n){
                _end->parent = n;
                n->leftC = _end;
                n->rightC = _end;
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
                
                if (tmp == _end){
                    root = _alloc.allocate(1);
                    _alloc.construct(root, node_type(p));
                    setEndAfter(root);
                    _size++;
                }
                while (tmp != _end){
                    if (!_comp(p,tmp->pair) && !_comp(tmp->pair, p))
                        return T(tmp->pair.first, 0);
                    tmp2 = compare(p, tmp);
                    if (tmp2 == tmp || tmp2 == _end)
                        break;
                    else 
                        tmp = tmp2;
                }
                if (_comp(p, tmp->pair)){
                    (tmp->leftC) = _alloc.allocate(1);
                    _alloc.construct((tmp->leftC), node_type(p, tmp, NULL, NULL));
                    setEndAfter(tmp->leftC);
                    _size++;
                }
                else{
                    (tmp->rightC) = _alloc.allocate(1);
                    _alloc.construct((tmp->rightC), node_type(p, tmp, NULL, NULL));
                    setEndAfter(tmp->rightC);
                   _size++;   
                }
                return p;
            }         

            void deleteNode(T p){
                node* toDelete = findNode(p);

                if (toDelete == _end)
                    return;
                deleteNode(toDelete);}


            void deleteNode(node* toDelete){        
                bool isLeftChild = false;

                if (toDelete->parent) //is toDelete a left Child ?
                    isLeftChild = (toDelete->parent->leftC == toDelete); 

                if (toDelete->leftC == _end && toDelete->rightC == _end){ // No Child
                    if (toDelete->parent){
                
                        isLeftChild ? toDelete->parent->leftC = _end : toDelete->parent->rightC = _end;
                        toDelete->leftC = NULL;
                        toDelete->rightC = NULL;
                        
                        _alloc.destroy(toDelete);
                        _alloc.deallocate(toDelete, 1);
                        _size--;

                        return ;
                    }
                    else{
                        _alloc.destroy(toDelete);
                        _alloc.deallocate(toDelete, 1);
                        root = _end;
                        _size--;

                        return ;
                    }
                }
     
                //One Child
                if ((toDelete->rightC && toDelete->leftC == _end) || (toDelete->rightC == _end && toDelete->leftC)){
                    bool hasLeftChild = (toDelete->leftC != _end ? true : false); // toDelete has a left child
            
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
                    _size--;

                    return ;
                }

                //Two Child
                else if (toDelete->leftC && toDelete->rightC){
                    node *prevToDelete = findPrevious(toDelete);

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
                    _size--;

                    deleteNode(prevToDelete);
                }
            }

            node* findNode(T p){
                node *findMe= _alloc.allocate(1);
                _alloc.construct(findMe, node_type(p));
                node *treeNode = root;

                while(_comp(findMe->pair,treeNode->pair) || _comp(treeNode->pair,findMe->pair)){ 
                    if (!_comp(findMe->pair, treeNode->pair)){
                        treeNode = findNext(treeNode);
                        if (treeNode == _end){
                            break;
                        }
                    }   
                    else if (_comp(findMe->pair, treeNode->pair))   
                        treeNode = findPrevious(treeNode);  
                        if (treeNode == _end)
                            break;   
                }
                _alloc.destroy(findMe);
                _alloc.deallocate(findMe, 1);
                return treeNode;
            }

            node *findMin(){ 
                if (root == _end){
                    return _end;
                }
                return root->findMin(_end);
            }

            node *findMin(node *n){
               return n->findMin(_end);
            }

            node* findMax(){
                if (root == _end){
                    return _end;
                }
                return root->findMax(_end);
            }

            node* findMax(node *n){ 
                return n->findMax(_end);
            }

            node* findNext(node *n){
                return n->findNext(_end);
            }

            node* findPrevious(node *n){
                return n->findPrevious(_end);
            }


            treeIterator<T, Compare> begin(){
                return treeIterator<T, Compare>(findMin());
            }

            treeIterator<T, Compare> end(){
                return treeIterator<T, Compare>(_end);
            }

            treeIterator<T, Compare> rbegin(){
                return treeIterator<T, Compare>(findMax());
            }

            treeIterator<T, Compare> rend(){
                return treeIterator<T, Compare>(_end);
            }

            void clear(){
                node* tmp = findMin();
                node* toDel = tmp;
                while (tmp){
                    tmp = findNext(tmp);
                    if(!tmp)
                        break;
                    deleteNode(toDel);
                    toDel = tmp;
                }
                root = _end;
                _size = 0;
            }
        
            size_t count(const T& k) {
                if (findNode(k) == _end)
                    return (0);
                else
                    return (1);
            }

            treeIterator<T, Compare> lower_bound (const T& k){
                node *ret = findNode(k);

                if (ret != _end) // on a trouvé la clé exacte, on la retourne
                    return treeIterator<T, Compare>(ret);
                else //on a pas trouvé, on va chercher la valeur qui va apres
                {
                    node *findMe= _alloc.allocate(1);
                    _alloc.construct(findMe, node_type(k));
                    node *treeNode = findMin();

                    while(_comp(treeNode->pair,findMe->pair) && treeNode != _end){ //tant que le findMe est plus petit que le treenode, on next treenode
                        treeNode = findNext(treeNode);
                    }   
                    _alloc.destroy(findMe);
                    _alloc.deallocate(findMe, 1);
                    return treeIterator<T, Compare>(treeNode);
                }
            }

            treeIterator<T, Compare> upper_bound (const T& k){
                 node *findMe= _alloc.allocate(1);
                _alloc.construct(findMe, node_type(k));
                node *treeNode = findMin();

                while((!(!_comp(treeNode->pair,findMe->pair) && !_comp(findMe->pair,treeNode->pair))) 
                        && _comp(treeNode->pair,findMe->pair) 
                        && treeNode != _end){ //pas d'egalité, treenode < findMe et pas a la fin => next TreeNode
                    treeNode = findNext(treeNode);
                }   
                _alloc.destroy(findMe);
                _alloc.deallocate(findMe, 1);
                return treeIterator<T, Compare>(treeNode);
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
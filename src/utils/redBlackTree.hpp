#pragma once
#include <iostream>
#define RED 1
#define BLACK 0
#include "binary_function.hpp"
#include "../iterators/treeIterator.hpp"
#include "pair.hpp"
#include "redBlackNode.hpp"

namespace ft{

    

    template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
    class BsT {

        public:

            typedef Compare             value_compare;

            // template <class T, class Compare, class Alloc >
            // class BsT<T, Compare, Alloc>::node;
            class node;


            typedef typename Alloc::template rebind<node>::other allocator_type;

        private:


            // var privee de tree :

            node*                   _root;
            node*                   _end;
            const value_compare     &_comp;
            allocator_type          _alloc;
            size_t                  _size;

        public:


            /*-----------------CONSTRUCTORS/DESTRUCTOR-------------*/

            ~BsT() {
                node* tmp = findMin();
                node* toDel = tmp;
                while (tmp != _end){
                    tmp = findNext(tmp);
                    deleteNode(toDel);
                    toDel = tmp;
                }
                _alloc.destroy(_end);
                _alloc.deallocate(_end, 1);
            }

            explicit BsT(const value_compare& comp = value_compare()) : _comp(comp){
                _end = _alloc.allocate(1);
                _alloc.construct(_end, node(_end, comp));
                _root = _end;
                _size = 0;
            }

            BsT(const BsT &src) : _comp(src._comp), _alloc(src._alloc), _size(0) {
                _end = _alloc.allocate(1);
                _alloc.construct(_end, node(_end, _comp));
                _root = _end;
                treeIterator<T, value_compare, Alloc> it = src.begin();
                treeIterator<T, value_compare, Alloc> ite = src.end();
                for(; it != ite; ++it){
                    insert_val(*it);
                }
            }

            /*----------OPERATOR OVERLOADS-------------*/

            BsT &operator=(BsT const &rhs){
                this->clear();
                treeIterator<T, value_compare, Alloc> it = rhs.begin();
                treeIterator<T, value_compare, Alloc> ite = rhs.end();
                for(; it != ite; ++it){
                    insert_val(*it);
                }
                return *this;
            }

            /*-------------GETTERS AND SETTERS----------------*/

            node* getRoot() const{
                return _root;
            }

            void setRoot(node* ptr){
                this->_root = ptr;
            }

            size_t getSize() const{
                return _size;
            }

            node* getEnd() const {
                return _end;
            }

            void setEnd(node* ptr){
                this->_end = ptr;
            }

            void    setNewRoot(node* root) //if you have to change the root, use this method instead of "="
            {
                _root = root;
                root->col = BLACK;
                _end->end = root; //useless to have end inside of end so we put the root instead (useful for --end)
            }

            void setEndAfter(node *n){
                n->leftC = _end;
                n->rightC = _end;
            }  



            /* -----------INSERTS------------- */

            //HERE
            node* insertNode(T p){
                if (_root == _end){
                    _root = _alloc.allocate(1);
                    _alloc.construct(_root, node(_end, p, NULL, _end, _end, _comp));
                    setNewRoot(_root);
                    _size++;
                    return _root;
                }

                node *tmp = _root;
                node *tmp2 = NULL;
                while (tmp != _end){
                    tmp2 = tmp;
                    if (_comp(p, tmp->pair)) //tmp > p
                        tmp = tmp->leftC;
                    else if (_comp(tmp->pair, p)) // p > tmp
                        tmp = tmp->rightC;
                    else
                        return NULL;
                }
                tmp = _alloc.allocate(1);
                _alloc.construct(tmp, node(_end, p, tmp2, _end, _end, _comp));
                _size++;
                (_comp(p, tmp2->pair)) ? tmp2->leftC = tmp : tmp2->rightC = tmp;
                fixInsert(tmp);
                return tmp;
            }         

            pair<treeIterator<T, Compare>, bool> insert_val(const T& val){

                pair<treeIterator<T, Compare>, bool> ret;
                node* tmp = findNode(val);

                if (tmp != _end){
                    ret.first = treeIterator<T, Compare>(tmp);
                    ret.second = false;
                    return ret;
                }
                else{
                    ret.first = treeIterator<T, Compare>(insertNode(val));
                    ret.second = true;
                }
                return ret;
            }

            node* insertNodeHint(node* hint,const T& val){
                
                node* tmp = hint;

                if (tmp->rightC == _end){
                    tmp->rightC = _alloc.allocate(1);
                    _alloc.construct((tmp->rightC), node(_end, val, tmp, NULL, NULL, _comp));
                    setEndAfter(tmp->rightC);
                    tmp = tmp->rightC;
                }
                else{
                    tmp = tmp->findNext();
                    tmp->leftC = _alloc.allocate(1);
                    _alloc.construct((tmp->leftC), node(_end, val, tmp, NULL, NULL, _comp));
                    setEndAfter(tmp->leftC);
                    tmp = tmp->leftC;
                    //fixInsert(tmp);
                }
                _size++;
                return tmp;
            }

            node* insertHint(node* hint, const T& val){
                
                node* ret;

                if (hint != _root->findMin() && hint != _root->findMax() && _comp(hint->pair, val) && _comp(val, (hint->findNext())->pair)){
                    ret = insertNodeHint(hint, val);
                }
                else{
                    node* tmp = findNode(val);
                    if (tmp == _end)
                        ret = insertNode(val);
                    else
                        return NULL;
                }
                return ret;
            }



            /*--------DELETE----------*/


            size_t deleteNode(T p){

                node* toDelete = findNode(p);

                if (toDelete == _end)
                    return 0;
                else{
                    deleteNode(toDelete);
                    return 1;
                }
            }


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
                        _root = _end;
                        _size--;

                        return ;
                    }
                }
     
                //One Child
                if ((toDelete->rightC && toDelete->leftC == _end) || (toDelete->rightC == _end && toDelete->leftC)){
                    bool hasLeftChild = (toDelete->leftC != _end ? true : false); // toDelete has a left child
            
                    if (toDelete == _root){
                        hasLeftChild ? setNewRoot(toDelete->leftC) : setNewRoot(toDelete->rightC);
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
                    _alloc.construct(substitute, node(_end, prevToDelete->pair, toDelete->parent, toDelete->leftC, toDelete->rightC, _comp));
                    //substitute == red ?
                    if (toDelete == _root)
                        setNewRoot(substitute);
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

            void clear(){
                node* tmp = findMin();
                node* toDel = tmp;
                while (tmp){
                    tmp = findNext(tmp);
                    if(tmp == _end)
                        break;
                    deleteNode(toDel);
                    toDel = tmp;
                }
                _root = _end;
                _size = 0;
            }




            /*----------FINDERS------------*/


            node* findNode(T p) const{
                node findMe(_end, p, _comp);
                node *currentNode = _root;


                if (currentNode == _end)
                    return _end;

                while ((_comp(findMe.pair,currentNode->pair) ||  _comp(currentNode->pair,findMe.pair)) && currentNode != _end){
                    if(_comp(findMe.pair,currentNode->pair)){
                        currentNode = currentNode->leftC;
                    }
                    else if (_comp(currentNode->pair,findMe.pair)){
                        currentNode = currentNode->rightC;
                    }
                }

                return currentNode;
            }

            node *findMin() const{ 
                if (_root == _end){
                    return _end;
                }
                return _root->findMin();
            }

            node *findMin(node *n) const{
               return n->findMin();
            }

            node* findMax() const{
                if (_root == _end){
                    return _end;
                }
                return _root->findMax();
            }

            node* findMax(node *n) const{ 
                return n->findMax();
            }

            node* findNext(node *n) const{
                return n->findNext();
            }

            node* findPrevious(node *n) const{
                return n->findPrevious();
            }


            treeIterator<T, Compare> begin() const{
                return treeIterator<T, Compare>(findMin());
            }

            treeIterator<T, Compare> end()const{
                return treeIterator<T, Compare>(_end);
            }

            treeIterator<T, Compare> rbegin()const{
                return treeIterator<T, Compare>(findMax());
            }

            treeIterator<T, Compare> rend()const{
                return treeIterator<T, Compare>(_end);
            }
        
            size_t count(const T& k)  const{
                if (findNode(k) == _end)
                    return (0);
                else
                    return (1);
            }

            node* lower_bound (const T& k) const{
                node *ret = findNode(k);

                if (ret != _end) // on a trouvé la clé exacte, on la retourne
                    return (ret);
                else //on a pas trouvé, on va chercher la valeur qui va apres
                {
                    node    findMe = node(_end, k, _comp);
                    node *treeNode = findMin();

                    while(_comp(treeNode->pair,findMe.pair) && treeNode != _end){ //tant que le findMe est plus petit que le treenode, on next treenode
                        treeNode = findNext(treeNode);
                    }   
                    return (treeNode);
                }
            }

            node* upper_bound (const T& k) const{
                node findMe = node(_end, k, _comp);
                node *treeNode = findMin();

                while( ( (!_comp(treeNode->pair,findMe.pair) && !_comp(findMe.pair,treeNode->pair)) 
                        || _comp(treeNode->pair,findMe.pair) )
                        && treeNode != _end){ //pas d'egalité, treenode < findMe et pas a la fin => next TreeNode
                    treeNode = findNext(treeNode);
                }   
                return (treeNode);
            }

        void leftRot(node* n){
            node* tmp = (n->rightC->leftC);

            if (n == _root){
                _root = n->rightC;
            }
            else {
    
                bool isLeftChild = (n->parent->leftC == n ? true : false);
                if (isLeftChild)
                    n->parent->leftC = n->rightC;
                else
                    n->parent->rightC = n->rightC;
            }
            n->rightC->leftC = n; 
            n->rightC->parent = n->parent; 
            n->parent = n->rightC; 
            n->rightC = tmp; 
            tmp->parent = n; 
        }



        void rightRot(node* n){
            node* tmp = (n->leftC->rightC);

            if (n == _root){
                _root = n->leftC;
            }
            else {
                bool isLeftChild = (n->parent->leftC == n ? true : false);
                if (isLeftChild)
                    n->parent->leftC = n->leftC;
                else
                    n->parent->rightC = n->leftC;
            }
            n->leftC->rightC = n;
            n->leftC->parent = n->parent;
            n->parent = n->rightC;
            n->leftC = tmp;
            tmp->parent = n;
        }

        void recolor(node* n){
            n->col = !n->col;
        }

        void colorRed(node *n){
            n->col = RED;
        }

        void colorBlack(node *n){
            n->col = BLACK;
        }

        void fixInsert(node* n){
            node* parent = n->parent;
            //proteger si pas de grandparent
            if (parent->col == BLACK)
                return;

            node* gParent = parent->parent;
            node* uncle = (gParent->leftC == parent ? gParent->rightC : gParent->leftC);
                std::cout << "tagadatsointsoin" << std::endl;
            node* sib = (parent->leftC == n ? parent->rightC : parent->leftC);

            if(uncle->col == RED){

                recolor(parent);
                recolor(uncle);
                if (gParent != _root)
                    recolor(gParent);
            }
            else{
                bool parentIsRightChild = ((gParent->rightC == parent ? true : false));
                bool nodeIsRightChild = ((parent->rightC == n ? true : false));

                if (parentIsRightChild && nodeIsRightChild){
                    leftRot(gParent);
                    sib = gParent;
                    sib->col = RED;
                    parent->col = BLACK;
                }
                else if (parentIsRightChild && !nodeIsRightChild){
                    rightRot(parent);
                    leftRot(n->parent);
                    sib = (n->parent->rightC == n ? n->parent->leftC : n->parent->rightC);
                    sib->col = RED;
                    n->parent->col = BLACK;
                }
                else if(!parentIsRightChild && !nodeIsRightChild) //debut de la version mirror
                {
                    rightRot(gParent);
                    sib = gParent;
                    sib->col = RED;
                    parent->col = BLACK;
                }
                else if (!parentIsRightChild && !nodeIsRightChild){
                    leftRot(parent);
                    rightRot(n->parent);
                    sib = (n->parent->rightC == n ? n->parent->leftC : n->parent->rightC);
                    sib->col = RED;
                    n->parent->col = BLACK;
                }
            }
        }

        void fixDelete(node* n){

            if (n->col == RED)
                return;
            node* redChild = (n->leftC->col == RED ? n->leftC : n->rightC);
            if(n->leftC->col == RED || n->rightC.col == RED){

            }

            while(n != _root && n->col == BLACK){
                //has a red child ? whatever ....
                    if(n->parent->leftC == n){

                        node* sib = (parent->leftC == n ? parent->rightC : parent->leftC);
                        bool sibIsRed = (sib->col == RED ? true : false);

                        if(sibIsRed){
                            recolor(sib);
                            recolor(n->parent);
                            leftRot(n->parent);
                        }
                        else if (!sibIsRed && sib->leftC->col == BLACK && sib->rightC->col == BLACK){
                            sib->col = RED;
                            if(n->parent == RED){
                                recolor(n->parent)
                                return;
                            }
                            fixDelete(n->parent);
                        }
                        else if (!sibIsRed && sib->leftC->col == BLACK && sib->rightC->col == BLACK){
                            recolor(sib);
                            recolor(sib->leftC);
                            rightRot(sib);

                            sib = (parent->leftC == n ? parent->rightC : parent->leftC);
                            sib->rightC->col = BLACK;
                            n->parent->col = BLACK;
                            leftRot(n->parent);
                        }
                        else if (!sibIsRed && sib->rightC->col == RED){
                            sib->rightC->col = BLACK;
                            n->parent->col = BLACK;
                            leftRot(n->parent);
                        }
                    }
                    else if (n->parent->rightC == n){
                        else if(sibIsRed){
                            recolor(sib);
                            recolor(n->parent);
                            rightRot(n->parent);
                        }
                        else if (!sibIsRed && sib->rightC->col == BLACK && sib->leftC->col == BLACK){
                            sib->col = RED;
                            if(n->parent == RED){
                                recolor(n->parent)
                                return;
                            }
                            fixDelete(n->parent);
                        }
                        else if (!sibIsRed && sib->rightC->col == BLACK && sib->leftC->col == BLACK){
                            recolor(sib);
                            recolor(sib->rightC);
                            rightRot(sib);

                            sib = (parent->rightC == n ? parent->leftC : parent->rightC);
                            sib->leftC->col = BLACK;
                            n->parent->col = BLACK;
                            rightRot(n->parent);
                        }
                        else if (!sibIsRed && sib->leftC->col == RED){
                            sib->leftC->col = BLACK;
                            n->parent->col = BLACK;
                            rightRot(n->parent);
                        }

                    }

            }
        }
    };
    
}
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

            class node;
            typedef Compare             value_compare;
            typedef typename Alloc::template rebind<node>::other allocator_type;

        private:

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

            void    setNewRoot(node* root)
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
                tmp->col = RED;
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
                }
                tmp->col = RED;
                fixInsert(tmp);
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
                node* toFix;

                if (toDelete->parent) //is toDelete a left Child ?
                    isLeftChild = (toDelete->parent->leftC == toDelete); 

                if (toDelete->leftC == _end && toDelete->rightC == _end){ // No Child
                    if (toDelete->parent){
                        toDelete->leftC = NULL;
                        toDelete->rightC = NULL;
                        fixDelete(toDelete);
                        isLeftChild ? toDelete->parent->leftC = _end : toDelete->parent->rightC = _end;
                        
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
                    bool hasLeftChild = (toDelete->leftC != _end ? true : false);                                       // toDelete has a left child
                    bool childIsRed = (hasLeftChild ? (toDelete->leftC->col == RED) : (toDelete->rightC->col == RED));
            
                    if (toDelete == _root){
                        hasLeftChild ? setNewRoot(toDelete->leftC) : setNewRoot(toDelete->rightC);
                        toFix = _root;
                    }
                    else if (isLeftChild){
                        hasLeftChild ? toDelete->parent->leftC = toDelete->leftC : toDelete->parent->leftC = toDelete->rightC;
                        toFix = toDelete->parent->leftC;
                    }
                    else{
                        hasLeftChild ? toDelete->parent->rightC = toDelete->leftC : toDelete->parent->rightC = toDelete->rightC;
                        toFix = toDelete->parent->rightC;
                    }
                    hasLeftChild ? toDelete->leftC->parent = toDelete->parent : toDelete->rightC->parent = toDelete->parent;
                    toFix->col = toDelete->col;
                    _size--;
                    if (toFix->col == BLACK && !childIsRed){
                        fixDelete(toFix);
                    _alloc.destroy(toDelete);
                    _alloc.deallocate(toDelete, 1);
                    }
                    return ;
                }

                //Two Children
                else if (toDelete->leftC && toDelete->rightC){
                    node *prevToDelete = findPrevious(toDelete);

                    node *substitute = _alloc.allocate(1);
                    _alloc.construct(substitute, node(_end, prevToDelete->pair, toDelete->parent, toDelete->leftC, toDelete->rightC, _comp));
                    substitute->col = toDelete->col; //
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
                    if(tmp == _end){
                        _root = _end;
                        _size = 0;
                        break;
                    }
                    deleteNode(toDel);
                    toDel = tmp;
                }
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
                node	*current = _root;
                node	*previous = NULL;
            
                while (current != _end)
                {
                    previous = current;
                    if (!_comp(current->pair, k) && !_comp(k, current->pair))
                        return current;
                    else if (_comp(current->pair, k))
                        current = current->rightC;
                    else
                        current = current->leftC;
                }
                if (!previous)
                    return this->_end;
                else if ( _comp(previous->pair, k))
                    return previous->findNext();
                return previous;
            }

            node* upper_bound (const T& k) const{
                node	*current = _root;
                node	*previous = NULL;
            
                while (current != _end)
                {
                    previous = current;
                    if (!_comp(current->pair, k) && !_comp(k, current->pair))
                        return current->findNext();
                    else if (_comp(current->pair, k))
                        current = current->rightC;
                    else
                        current = current->leftC;
                }
                if (!previous)
                    return this->_end;
                else if ( _comp(previous->pair, k))
                    return previous->findNext();
                return previous;
            }

        void leftRot(node* n){
            node* tmp = (n->rightC->leftC);

            if (n == _root){
                setNewRoot(n->rightC);
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
            if (n)
                n->parent = n->rightC; 
            n->rightC = tmp; 
            if (tmp && tmp != _end)
                tmp->parent = n;
        }



        void rightRot(node* n){
            node* tmp = (n->leftC->rightC);

            if (n == _root){
                setNewRoot(n->leftC);
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
            if (n)
                n->parent = n->leftC;
            n->leftC = tmp;
            if (tmp && tmp != _end)
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
            while (n->parent && n->parent->col == RED && n->parent->parent){
                node* parent = n->parent;
                node* gParent = parent->parent;
                node* uncle = (gParent->leftC == parent ? gParent->rightC : gParent->leftC);

                if(uncle->col == RED){
                    colorBlack(uncle);
                    colorBlack(parent);
                    colorRed(gParent);
                    n = gParent;
                }
                else if (parent == gParent->rightC)
                {                  
                    if (n == parent->leftC)
                    {
                        n = n->parent;
                        rightRot(n);
                        parent = n->parent;
                        gParent = parent->parent;
                    }
                    colorBlack(parent);
                    colorRed(gParent);
                    leftRot(gParent);
                }
                else if (parent == gParent->leftC)
                {
                    if (n == parent->rightC)
                    {
                        n = n->parent;
                        leftRot(n);
                        parent = n->parent;
                        gParent = parent->parent;
                    }
                    colorBlack(parent);
                    colorRed(gParent);
                    rightRot(gParent);
                }
            }
            colorBlack(this->_root);

        }

        void fixDelete(node* n){
            while(n != _root && n->col == BLACK){
                if (n == n->parent->leftC)
                {
                    node *sib = n->parent->rightC;
                    if (sib->col == RED)
                    {
                        sib->col = BLACK;
                        n->parent->col = RED;
                        leftRot(n->parent);
                        sib = n->parent->rightC;
                    }
                    if (sib->col == BLACK && sib->leftC->col == BLACK && sib->rightC->col == BLACK)
                    {
                        sib->col = RED;
                        n = n->parent;
                    }
                    else 
                    {
                        if (sib->rightC->col == BLACK)
                        {
                            sib->leftC->col = BLACK;
                            sib->col = RED;
                            rightRot(sib);
                            sib = n->parent->rightC;
                        }
                        sib->col = n->parent->rightC;
                        n->parent->col = BLACK;
                        sib->rightC->col = BLACK;
                        leftRot(n->parent);
                        n = _root;
                    }
                }
                else if (n == n->parent->rightC)
                {
                    node *sib = n->parent->leftC;
                    if (sib->col == RED)
                    {
                        sib->col = BLACK;
                        n->parent->col = RED;
                        leftRot(n->parent);
                        sib = n->parent->leftC;
                    }
                    if (sib->col == BLACK && sib->rightC->col == BLACK && sib->leftC->col == BLACK)
                    {                    
                        sib->col = RED;
                        n = n->parent;
                    }
                    else 
                    {
                        if (sib->leftC->col == BLACK)
                        {                    
                            sib->rightC->col = BLACK;
                            sib->col = RED;
                            leftRot(sib);
                            sib = n->parent->leftC;
                        }                    
                        sib->col = n->parent->leftC;
                        n->parent->col = BLACK;
                        sib->leftC->col = BLACK;
                        rightRot(n->parent);
                        n = _root;
                    }
                }
            }
            n->col = BLACK;
        }

        void printBT(const std::string& prefix, const node* n, bool isLeft)
            {
                if( n != NULL )
                {
                    std::cout << prefix;

                    std::cout << (isLeft ? "├──" : "└──" );

                    // print the value of the n
                    if (n == _end)
                        std::cout << "end" << std::endl;
                    else if (n->col == RED)
                        std::cout << "\033[1;31m" << n->pair.first << "\033[0m" << std::endl;
                    else
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
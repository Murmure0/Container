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
                _end->end = root; //useless to have end inside of end so we put the root instead (useful for --end)
            }

            void setEndAfter(node *n){
                n->leftC = _end;
                n->rightC = _end;
            }  



            /* -----------INSERTS------------- */

            node *compare(T p, node *n){
                if (_comp(p, n->pair) && n->leftC)
                    return (n->leftC);
                else if(_comp(n->pair, p) && n->rightC)
                    return (n->rightC);
                else
                    return n;
            }

            node* insertNode(T p){
                node *tmp = _root;
                node *tmp2 = NULL;
                if (tmp == _end){
                    _root = _alloc.allocate(1);
                    _alloc.construct(_root, node(_end, p, _comp));
                    setEndAfter(_root);
                    setNewRoot(_root);
                    _size++;
                    if (_root->leftC == _end && _root->rightC == _end){
                    }
                    return _root;
                }
                while (tmp != _end){
                    if (!_comp(p,tmp->pair) && !_comp(tmp->pair, p))
                        return NULL;
                    tmp2 = compare(p, tmp);
                    if (tmp2 == tmp || tmp2 == _end)
                        break;
                    else 
                        tmp = tmp2;
                }
                if (_comp(p, tmp->pair)){
                    (tmp->leftC) = _alloc.allocate(1);
                    _alloc.construct((tmp->leftC), node(_end, p, tmp, NULL, NULL, _comp));
                    setEndAfter(tmp->leftC);
                    _size++;
                    return tmp->leftC;
                }
                else if (_comp(tmp->pair, p)){
                    (tmp->rightC) = _alloc.allocate(1);
                    _alloc.construct((tmp->rightC), node(_end, p, tmp, NULL, NULL, _comp));
                    setEndAfter(tmp->rightC);
                   _size++;  
                   return tmp->rightC;
                }
                return NULL;
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

    };
    
}
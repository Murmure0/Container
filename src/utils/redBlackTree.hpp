#pragma once
#include <iostream>
#define RED 1
#define BLACK 0
#include "binary_function.hpp"
#include "../iterators/treeIterator.hpp"
#include "pair.hpp"

namespace ft{

    template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
    class BsT {

        public:

            typedef Compare             value_compare;
        

            class node {

                public:

                    const value_compare &comp;
                    T       pair;
                    node*   parent;
                    node*   leftC;
                    node*   rightC;
                    node*   end;
                    bool    col;

                    explicit node(node* e, const value_compare& comp = value_compare()) : comp(comp), pair(), end(e) {
                        parent = NULL;
                        leftC = NULL;
                        rightC = NULL;
                        col = BLACK;
                            // std::cout << "constructeur par defaut node : adresse de end : " << end << "and e : " << e << std::endl;
                    }

                    node(node* e, T p, const value_compare& comp = value_compare()) : comp(comp), pair(p), end(e) {
                        parent = NULL;
                        leftC = NULL;
                        rightC = NULL;
                        col = BLACK;
                            // std::cout << "constructeur par value node : adresse de end : " << end << std::endl;
                    }

                    node(node* e,T p, node*par, node*lC, node*rC, const value_compare& comp = value_compare())
                     : comp(comp), pair(p), parent(par), leftC(lC), rightC(rC), end(e) {
                        col = BLACK;
                    }

                    ~node() {
                    }

                    /*
                    */
                   	operator				typename BsT<const T, Compare>::node() const
	                {
		                return BsT<const T, Compare>::node(*this);
                    }

                    node(node const &src) : comp(src.comp), pair(src.pair), parent(src.parent), leftC(src.leftC), rightC(src.rightC), end(src.end), col(src.col) {}

                    node* getEnd(){
                        return this->end;
                    }

                    node &operator=(node const &rhs){
                        // pair = rhs.pair;
                        // std::cout << "YOU SHOULDNT BE THERE" << std::endl;
                        parent = rhs.parent; 
                        leftC = rhs.leftC; 
                        rightC = rhs.rightC; 
                        col = rhs.col;
                        end = rhs.end;
                        return *this;
                    }

                    node *findMin(){
                        node *tmp = this;

                        while (tmp->leftC && tmp->leftC != end){
                            tmp = tmp->leftC;
                        }
                        return tmp;
                    }

                    node* findMax(){
                        node *tmp = this;
                        
                        while (tmp->rightC && tmp->rightC != end){
                            tmp = tmp->rightC;
                        }
                        return tmp;
                    }

                    node* findNext(){
                        node* tmp = this;

                        //s'il y a une branche a droite, on cherche la plus petite valeur
                        if (tmp->rightC && tmp->rightC != end){
                            tmp = tmp->rightC;
                            return (tmp->findMin());
                        }
                        //sinon on remonte dans le parent 
                        else if (tmp->parent){
                            while (tmp->parent && comp(tmp->parent->pair, tmp->pair)){
                                tmp = tmp->parent;
                            }
                            if( tmp->parent ){
                                return tmp->parent;
                            }
                        }
                        return end;
                    }

                    node* findPrevious(){

                        //qd on est sur le node end ca va cracher, bisou, faudra renvoyer root.findmax()

                        node* tmp = this;
                        if (tmp->leftC){
                            tmp = tmp->leftC;
                            return tmp->findMax();
                        }
                        else {
                            while(tmp->parent && comp(tmp->pair, tmp->parent->pair))
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

            node*                   _root;
            node*                   _end;
            const value_compare     &_comp;
            allocator_type          _alloc;
            size_t                  _size;

        public:

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
                _alloc.construct(_end, node_type(_end, comp));
                _root = _end;
                _size = 0;
            }

            // BsT(T p, value_compare& comp = value_compare()) : _comp(comp) {
            //     _root = _alloc.allocate(1);
            //     _alloc.construct(_root, node_type(p));
            //     _end = _alloc.allocate(1);
            //     _alloc.construct(_end, node_type());
            //     setEndAfter(_root);
            //     _size = 1;
            // }

            BsT &operator=(BsT const &rhs){
                _root = rhs._root;
                _end = rhs._end; 
                _size = rhs._size;
                return *this;
            }

            node* getRoot() const{
                return _root;
            }

            size_t getSize() const{
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

            node* insertNode(T p){
                node *tmp = _root;
                node *tmp2 = NULL;
                
                if (tmp == _end){
                    _root = _alloc.allocate(1);
                    _alloc.construct(_root, node_type(_end, p, _comp));
                    setEndAfter(_root);
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
                    _alloc.construct((tmp->leftC), node_type(_end, p, tmp, NULL, NULL, _comp));
                    setEndAfter(tmp->leftC);
                    _size++;
                    return tmp->leftC;
                }
                else{
                    (tmp->rightC) = _alloc.allocate(1);
                    _alloc.construct((tmp->rightC), node_type(_end, p, tmp, NULL, NULL, _comp));
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
                    _alloc.construct((tmp->rightC), node_type(_end, val, tmp, NULL, NULL, _comp));
                    setEndAfter(tmp->rightC);
                    tmp = tmp->rightC;
                }
                else{
                    tmp = tmp->findNext();
                    tmp->leftC = _alloc.allocate(1);
                    _alloc.construct((tmp->leftC), node_type(_end, val, tmp, NULL, NULL, _comp));
                    setEndAfter(tmp->leftC);
                    tmp = tmp->leftC;
                }
                _size++;  
                return tmp;
            }

            pair<treeIterator<T, Compare>, bool> insertHint(node* hint, const T& val){
                
                node* ret;

                if (hint != _root->findMin() && hint != _root->findMax() && _comp(hint->pair, val) && _comp((hint->findNext())->pair, val)){
                    ret = insertNodeHint(hint, val);
                }
                else{
                    node* tmp = findNode(val);
                    if (tmp == _end)
                        ret = insertNode(val);
                    else
                        ret = tmp;
                }
                return ret;
            }


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
                        hasLeftChild ? _root = toDelete->leftC : _root = toDelete->rightC;
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
                    _alloc.construct(substitute, node_type(_end, prevToDelete->pair, toDelete->parent, toDelete->leftC, toDelete->rightC, _comp));

                    if (toDelete == _root)
                        _root = substitute;
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

            node* findNode(T p) const{
                node findMe(_end, p, _comp);
                node *treeNode = _root;

                if (treeNode == _end)
                    return _end;

                while(_comp(findMe.pair,treeNode->pair) || _comp(treeNode->pair,findMe.pair)){ 
                    if (!_comp(findMe.pair, treeNode->pair)){
                        treeNode = findNext(treeNode);
                        if (treeNode == _end){
                            break;
                        }
                    }   
                    else if (_comp(findMe.pair, treeNode->pair))   
                        treeNode = findPrevious(treeNode);  
                        if (treeNode == _end)
                            break;   
                }
                // _alloc.destroy(findMe);
                // _alloc.deallocate(findMe, 1);
                return treeNode;
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
                _root = _end;
                _size = 0;
            }
        
            size_t count(const T& k)  const{
                if (findNode(k) == _end)
                    return (0);
                else
                    return (1);
            }

            treeIterator<T, Compare> lower_bound (const T& k) const{
                node *ret = findNode(k);

                if (ret != _end) // on a trouvé la clé exacte, on la retourne
                    return treeIterator<T, Compare>(ret);
                else //on a pas trouvé, on va chercher la valeur qui va apres
                {
                    node *findMe= _alloc.allocate(1);
                    _alloc.construct(findMe, node_type(_end, k, _comp));
                    node *treeNode = findMin();

                    while(_comp(treeNode->pair,findMe->pair) && treeNode != _end){ //tant que le findMe est plus petit que le treenode, on next treenode
                        treeNode = findNext(treeNode);
                    }   
                    _alloc.destroy(findMe);
                    _alloc.deallocate(findMe, 1);
                    return treeIterator<T, Compare>(treeNode);
                }
            }

            treeIterator<T, Compare> upper_bound (const T& k) const{
                node *findMe= _alloc.allocate(1); //faire ca sur la stack bisou
                _alloc.construct(findMe, node_type(_end, k, _comp));
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

            pair<treeIterator<T, Compare>,treeIterator<T, Compare> >             equal_range (const T& k) const{

                pair<const T, int> p(k, 0);
                pair<treeIterator<T, Compare>, treeIterator<T, Compare> > ret;

                if (findNode(p) != _end)
                {
                    treeIterator<T, Compare> low = lower_bound(k);
                    treeIterator<T, Compare> up = upper_bound(k);
                    ret = make_pair(low, up);
                }
                else
                {
                    treeIterator<T, Compare> up = upper_bound(k);
                    ret = make_pair(up, up);
                }
                    return ret;
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
#include "redBlackTree.hpp"
#include "pair.hpp"

int main(){
    ft::pair<int, int> b(30, 120);
    ft::pair<int, int> c(35, 120);
    ft::pair<int, int> e(20, 120);
    ft::pair<int, int> f(32, 120);
    ft::pair<int, int> g(38, 120);
    ft::pair<int, int> a(40, 120);
    ft::pair<int, int> d(36, 120);
    //ft::pair<int, int> h(33, 120);

    //ft::rdb< ft::pair<int, int> > nullTree;
    ft::rdb< ft::pair<int, int> > notTree(b);
    // notTree.print();
     notTree.insertNode(e);
    notTree.insertNode(c);
    notTree.insertNode(g);
    notTree.insertNode(f);
    // // notTree.print();
    notTree.insertNode(a);
    // // // notTree.print();
    // // // notTree.print();
    // // // notTree.print();
    notTree.insertNode(d);
    //notTree.insertNode(h);


    //std::cout << notTree.findMax(notTree.findMin())->pair.first << std::endl;
    
    notTree.printBT(notTree.getRoot());

    notTree.deleteNode(b); //10
   
    notTree.printBT(notTree.getRoot());
} 
#include "redBlackTree.hpp"
#include "pair.hpp"

int main(){
    ft::pair<int, int> b(30, 120);
     ft::pair<int, int> c(32, 120);
    ft::pair<int, int> f(35, 120);
    ft::pair<int, int> g(32, 120);
    ft::pair<int, int> a(38, 120);
    ft::pair<int, int> d(36, 120);
    ft::pair<int, int> h(40, 120);
    ft::pair<int, int> e(34, 120);
    ft::pair<int, int> i(31, 120);

    //ft::rdb< ft::pair<int, int> > nullTree;
    ft::rdb< ft::pair<int, int> > notTree(b);
    // notTree.print();
    notTree.insertNode(f);
    notTree.insertNode(c);
    notTree.insertNode(a);
    notTree.insertNode(g);
    // // notTree.print();
    // // // notTree.print();
    // // // notTree.print();
    // // // notTree.print();
    notTree.insertNode(d);
    notTree.insertNode(h);
     notTree.insertNode(e);
     notTree.insertNode(i);


    //std::cout << notTree.findMax(notTree.findMin())->pair.first << std::endl;
    
    notTree.printBT(notTree.getRoot());

    notTree.deleteNode(f); //10
   
    notTree.printBT(notTree.getRoot());
} 
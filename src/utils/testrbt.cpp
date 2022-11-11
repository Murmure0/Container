#include "redBlackTree.hpp"
#include "pair.hpp"
#include "../iterators/treeIterator.hpp"


#include<map>


int main(){
    ft::pair<int, int> b(30, 120);
    //  ft::pair<int, int> c(29, 120);
    ft::pair<int, int> f(29, 120);
    ft::pair<int, int> g(40, 120);
    ft::pair<int, int> a(38, 120);
    ft::pair<int, int> d(36, 120);
    ft::pair<int, int> h(35, 120);
    // ft::pair<int, int> e(34, 120);
    // ft::pair<int, int> i(29, 120);

    //ft::rdb< ft::pair<int, int> > nullTree;
    ft::BsT< ft::pair<int, int> > notTree(b);
        

    // ft::rdb< ft::pair<int, int> > notTree;
    // notTree.print();
    notTree.insertNode(f);
    //std::cout << (notTree.getRoot())->pair.first << std::endl;
    // notTree.insertNode(f);
    notTree.insertNode(a);
    notTree.insertNode(d);
    notTree.insertNode(g);
//     // // notTree.print();
//     // // // notTree.print();
//     // // // notTree.print();
//     // // // notTree.print();
//    // notTree.insertNode(h);
//     notTree.insertNode(e);
//     notTree.insertNode(i);

// /*PRINT*/

//     ft::treeIterator< ft::pair<int, int> > it = notTree.begin();
//     // ft::treeIterator< ft::pair<int, int> > ite = notTree.end();

//     std::map<int,int> pom;
//     pom[1] = 25;
//     pom[2] = 30;
//     pom[3] = 35;
//     pom[4] = 40;

//     std::map<int,int> mop(pom.begin(), pom.end());
//     std::map<int,int>::iterator ito = mop.begin();
//     std::map<int,int>::iterator itoe = mop.end();

//     std::cout << "mop : " << std::endl;
//     for(; ito != itoe; ito++){
//         std::cout << ito->first << " content: " << ito->second << std::endl;
//     }
//     //std::cout << notTree.findMax(notTree.findMin())->pair.first << std::endl;
    
 notTree.printBT(notTree.getRoot());

std::cout << "upper bound : "<< (notTree.upper_bound(h))->first << std::endl;

 notTree.printBT(notTree.getRoot());
//     std::cout << it->first << std::endl;
//     ++it;
//     std::cout << it->first << std::endl;
    // notTree.deleteNode(f); //10
   
    // notTree.printBT(notTree.getRoot());
    // std::cout << notTree.findNext(notTree.findNode(f))->pair.first << std::endl;
} 
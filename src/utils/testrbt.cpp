#include "redBlackTree.hpp"
#include "pair.hpp"
#include "../iterators/treeIterator.hpp"
#include "../containers/map.hpp"


#include<map>


int main(){
    ft::pair<int, int> b(30, 120);
    ft::pair<int, int> c(29, 120);
    ft::pair<int, int> f(29, 120);
    ft::pair<int, int> g(40, 120);
    ft::pair<int, int> a(38, 120);
    ft::pair<int, int> d(36, 120);
    ft::pair<int, int> h(35, 120);

    ft::map<int,int> mop;

    mop.insert(b);
    mop.insert(g);
    mop.insert(c);

    ft::map<int, int>::iterator it = mop.begin();
    ft::map<int, int>::iterator ite = mop.end();

 
    for(; it != ite; it++){
    std::cout << "Content it : " <<(*it).first << std::endl;
    }
} 
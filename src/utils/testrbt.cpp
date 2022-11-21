

#include "../containers/map.hpp"


#include<map>


int main(){
    ft::pair<int, std::string> a(42, "120");
    ft::pair<int, std::string> b(42, "120");
    ft::pair<int, std::string> c(50, "120");
    ft::pair<int, std::string> d(35, "120");
    ft::pair<int, std::string> e(45, "120");
    ft::pair<int, std::string> f(21, "120");
    ft::pair<int, std::string> g(38, "120");
    // ft::pair<int, std::string> h(35, "120");

    ft::map<int,std::string> mop;

    mop.insert(a);
    mop.insert(b);
    mop.insert(c);
    mop.insert(d);
    mop.insert(e);
    mop.insert(f);
    mop.insert(g);

    ft::map<int, std::string>::iterator it = mop.begin();
    ft::map<int, std::string>::iterator ite = mop.end();

 
    for(; it != ite; it++){
    std::cout << "Content it : " <<(*it).first << std::endl;
    }
    
} 
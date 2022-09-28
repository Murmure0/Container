#include "../containers/vector.hpp"
#include <vector>
#include <string>
#include <iostream>

int main()
{
    // std::vector<std::string> theirVector(5, std::string("lol"));
    // ft::vector<std::string> myVector(3, std::string("lol"));

    std::vector<int> theirVector(5, 25);
    /* contructor */
    ft::vector<int> myVector(3, 28);
    /* constructor by copy */
    ft::vector<int> foo(myVector);
    ft::vector<int> bar = foo;

    /* random_access_iterator */
    ft::vector<int>::iterator it = foo.begin();
    ft::vector<int>::iterator ite = foo.end();
    for(;it != ite; ++it)
        std::cout << *(it) << std::endl;

    ft::vector<int>::reverse_iterator rite = bar.rend();
    ft::vector<int>::reverse_iterator rit = bar.rbegin();
    // for(; rit != rite; ++rit)
    //     std::cout << *(rit) << std::endl;
    
}

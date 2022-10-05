#include "../containers/vector.hpp"
#include <vector>
#include <string>
#include <iostream>

int main()
{
     //std::vector<std::string> theirVector(5, std::string("lol"));
    // ft::vector<std::string> myVector(3, std::string("lol"));

    std::vector<int> theirVector(5, 25);

    std::cout << "empty constructor" << std::endl;
    std::cout << std::endl;
    ft::vector<int> emptyVector;

    std::cout << "myVector constructor" << std::endl;
    std::cout << std::endl;
    ft::vector<int> myVector(3, 28);
    ft::vector<int> secondVector(10, 89);

    std::cout << "mySuperVector constructor" << std::endl;
    ft::vector<ft::vector<int> > mySuperVector;
    std::cout << std::endl;

    /* constructor by copy */
    std::cout << "Constructor by copy foo" << std::endl;
    ft::vector<int> foo(myVector);
    std::cout << std::endl;

    std::cout << "Constructor by range of iterator fooFoo" << std::endl;
    ft::vector<int>::iterator it = foo.begin();
    ft::vector<int>::iterator ite = foo.end();
    ft::vector<int> fooFoo(it, ite);
    std::cout << std::endl;
    
    std::cout << "Constructor by operator=" << std::endl;
    ft::vector<int> bar = foo;
    std::cout << std::endl;

    std::cout << "random_access_iterator: " << std::endl;
    it = foo.begin();
    ite = foo.end();
    for(;it != ite; ++it)
        std::cout << *(it) << std::endl;
    std::cout << std::endl;

    std::cout << "Reverse_iterator: " << std::endl;
    ft::vector<int>::reverse_iterator rite = bar.rend();
    ft::vector<int>::reverse_iterator rit = bar.rbegin();
    for(; rit != rite; rit++)
        std::cout << *(rit) << std::endl;
    std::cout << std::endl;

    std::cout << " CAPACITY " << std::endl;
    std::cout << "Size of foo: " << foo.size() << std::endl;
    std::cout << std::endl;
    
    std::cout << "MaxSize of foo: " << foo.max_size() << std::endl;
    std::cout << std::endl;
    
    /* test apres pushback */
    // std::cout << "Resizing of foo to 1: "  << std::endl;
    // foo.resize(1);
    // ft::vector<int>::iterator it = foo.begin();
    // ft::vector<int>::iterator ite = foo.end();
    // for(;it != ite; ++it)
    //     std::cout << *(it) << std::endl;
    // std::cout << foo.size() << std::endl;
    // std::cout << "Resizing of foo to 10 with 19: "  << std::endl;
    // foo.resize(10, 19);
    // ft::vector<int>::iterator it = foo.begin();
    // ft::vector<int>::iterator ite = foo.end();
    // for(;it != ite; ++it)
    //     std::cout << *(it) << std::endl;
    // std::cout << std::endl;

    std::cout << "Capacity: " << foo.capacity() << std::endl;
    std::cout << std::endl;

    std::cout << "Empty: Is foo empty (0 = true, else false) ?  " << foo.empty() << std::endl;
    std::cout << "Is emptyVector really empty ? " << emptyVector.empty() << std::endl;
    std::cout << std::endl;

    std::cout << "Reserve: foo size : " << foo.size() << " foo capacity : " << foo.capacity() << std::endl;
    foo.reserve(2);
    std::cout << "foo.reserve(2), foo.size : " << foo.size() << " foo capacity: " << foo.capacity() << std::endl;
    std::cout << "foo content : " << std::endl;
    it = foo.begin();
    ite = foo.end();
    for(;it != ite; ++it)
        std::cout << *(it) << std::endl;
    std::cout << std::endl;
    foo.reserve(12);
    std::cout << "foo.reserve(12), foo.size : " << foo.size() << " foo capacity: " << foo.capacity() << std::endl;
    std::cout << "foo content : " << std::endl;
    it = foo.begin();
    ite = foo.end();
    for(;it != ite; ++it)
        std::cout << *(it) << std::endl;
    std::cout << std::endl;

    std::cout << "ELEMENT ACCESS " << std::endl;
    std::cout << "operator[] : foo index 2 : " << foo[2] << std::endl;
    std::cout << "operator at : foo index 2 : " << foo.at(2) << std::endl;

    std::cout << "front foo : " << foo.front() << std::endl;
    std::cout << "back foo : " << foo.back() << std::endl;

    
    std::cout << " MODIFIERS " << std::endl;

    std::cout << " Assign: " << std::endl;
    std::cout << " Foo can contain the content of secondVector: " << std::endl;
    std::cout << "content secondVector : " << std::endl;
    ft::vector<int>::iterator Sit = secondVector.begin();
    ft::vector<int>::iterator Site = secondVector.end();
    for (; Sit != Site; Sit++)
        std::cout << *Sit << std::endl;
    std::cout << std::endl;

    std::cout << "content foo : " << std::endl;
    std::cout << " foo capacity : " << foo.capacity() << std::endl;
    it = foo.begin();
    ite = foo.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;

    std::cout << "Assign, range version : foo.asign(first, last)" << std::endl;
    Sit = secondVector.begin();
    foo.assign(Sit, Site);
    ft::vector<int>::iterator mop = foo.begin();
    ft::vector<int>::iterator mope = foo.end();
    for (; mop != mope; mop++)
        std::cout << *mop << std::endl;
    std::cout << std::endl;
   
    std::cout << "The myVector can't contain the content of secondVector: " << std::endl;
    std::cout << " myVector capacity : " << myVector.capacity() << std::endl;
    std::cout << "content myVector : " << std::endl;
    it = myVector.begin();
    ite = myVector.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
   
    std::cout << "Assign, range version : myVector.asign(first, last)" << std::endl;
    Sit = secondVector.begin();
    Site = secondVector.end();
    myVector.assign(Sit, Site);
    it = myVector.begin();
    ite = myVector.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;

    std::cout << "Assign, fill version : myVector.assign(3,5)" << std::endl;
    myVector.assign(3,5);
    it = myVector.begin();
    ite = myVector.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;

    std::cout << "Push_back test :  myVector.push_back(7) " << std::endl;
    myVector.push_back(7);
    it = myVector.begin();
    ite = myVector.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    
    std::cout << "Pop_back test :  myVector.pop_back() " << std::endl;
    myVector.pop_back();
    it = myVector.begin();
    ite = myVector.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;
    
    std::cout << "Insert test : ito= myVector.begin() + 2 // myVector.insert(ito, 1989) " << std::endl;
    ft::vector<int> pbVector;
    pbVector.push_back(20);
    pbVector.push_back(19);
    pbVector.push_back(18);
    pbVector.push_back(17);
    pbVector.push_back(16);
    ft::vector<int>::iterator ito = (pbVector.begin()) + 2;
    ft::vector<int>::iterator ret = pbVector.insert(ito, 1989);
    std::cout << "Content of ret : " << *ret << std::endl;
    
    it = pbVector.begin();
    ite = pbVector.end();
    for (; it != ite; it++)
        std::cout << *it << std::endl;
    std::cout << std::endl;

    {
        std::cout << "Multi-Insert test " << std::endl;
        ft::vector<int> miVector;

        miVector.push_back(9);
        miVector.push_back(8);
        miVector.push_back(7);
        miVector.push_back(6);
        miVector.push_back(5);
        miVector.push_back(4);
        miVector.push_back(3);
        miVector.push_back(2);
        miVector.push_back(1);
        miVector.push_back(13);

        std::cout << std::endl;
        ito = (miVector.begin()) + 4;
        miVector.insert(ito, 2, 1989);
        
        it = miVector.begin();
        ite = miVector.end();
        for (; it != ite; it++)
            std::cout << *it << std::endl;
        std::cout << std::endl;
    }

    {
        std::cout << "Multi-Insert test with iterator " << std::endl;
        ft::vector<int> potiVector;

        potiVector.push_back(3);
        potiVector.push_back(2);
        potiVector.push_back(1);

        ft::vector<int> groVector;
        groVector.push_back(10);
        groVector.push_back(9);
        groVector.push_back(8);
        groVector.push_back(7);
        groVector.push_back(6);

        ft::vector<int>::iterator pit = potiVector.begin();
        ft::vector<int>::iterator pite = potiVector.end();
        ft::vector<int>::iterator git = groVector.begin()+1;
        groVector.insert(git, pit, pite);

        ft::vector<int>::iterator it = groVector.begin();
        ft::vector<int>::iterator ite = groVector.end();
        for (; it != ite; it++)
            std::cout << *it << std::endl;
        std::cout << std::endl;
    }
 


}

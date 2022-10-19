#include "../containers/stack.hpp"
#include <iostream>
#include <stack>

int main() {

    ft::stack<int> myVector;
    ft::stack<int> myVector2;
    ft::stack<int> myVector3;

    std::cout << "myVector.size(): " << myVector.size() <<std::endl;
    for(int i = 0; i < 25; i++){
        myVector.push(i);
        myVector2.push(i);
        myVector3.push(i);
    }
    std::cout << "PUSH : myVector.size(): " << myVector.size() <<std::endl;
    std::cout << "myVector.top(): " << myVector.top() <<std::endl;
    myVector.pop();
    std::cout << "POP : myVector.size(): " << myVector.size() <<std::endl;
    std::cout << "myVector.top(): " << myVector.top() <<std::endl;
    std::cout << "EMPTY : myVector.empty(): " << myVector.empty() << std::endl;
    for(int i = 0; i < 24; i++)
        myVector.pop();
    std::cout << "EMPTY : myVector.empty(): " << myVector.empty() << std::endl << std::endl;

    std::cout << "Operator == " << (myVector2 == myVector) << std::endl;
    std::cout << "Operator == " << (myVector2 == myVector3) << std::endl << std::endl;

    std::cout << "Operator != " << (myVector2 != myVector) << std::endl;
    std::cout << "Operator != " << (myVector2 != myVector3) << std::endl << std::endl;

    std::cout << "Operator < " << (myVector2 < myVector) << std::endl;
    std::cout << "Operator < " << (myVector2 < myVector3) << std::endl << std::endl;

    std::cout << "Operator <= " << (myVector2 <= myVector) << std::endl;
    std::cout << "Operator <= " << (myVector2 <= myVector3) << std::endl << std::endl;

    std::cout << "Operator > " << (myVector2 > myVector) << std::endl;
    std::cout << "Operator > " << (myVector2 > myVector3) << std::endl << std::endl;
    
    std::cout << "Operator >= " << (myVector2 >= myVector) << std::endl;
    std::cout << "Operator >= " << (myVector2 >= myVector3) << std::endl << std::endl;


    std::cout << "standard :" << std::endl<< std::endl;

    std::stack<int> stand;

    std::cout << "stand.size(): " << stand.size() <<std::endl;
    for(int i = 0; i < 25; i++)
        stand.push(i);
    std::cout << "PUSH : stand.size(): " << stand.size() <<std::endl;
    std::cout << "stand.top(): " << stand.top() <<std::endl;
    stand.pop();
    std::cout << "POP : stand.size(): " << stand.size() <<std::endl;
    std::cout << "stand.top(): " << stand.top() <<std::endl;
    std::cout << "EMPTY : stand.empty(): " << stand.empty() << std::endl;
    for(int i = 0; i < 24; i++)
        stand.pop();
    std::cout << "EMPTY : stand.empty(): " << stand.empty() << std::endl;
}
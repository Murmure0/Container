#include "../testStd.hpp"

void stackTest() {

    std::stack<int> myVector;
    std::stack<int> myVector2;
    std::stack<int> myVector3;

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
}
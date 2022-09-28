#include "../containers/vector.hpp"
#include <vector>
#include <string>

int main()
{
    // std::vector<std::string> theirVector(5, std::string("lol"));
    // ft::vector<std::string> myVector(3, std::string("lol"));

    std::vector<int> theirVector(5, 25);
    ft::vector<int> myVector(3, 28);
    ft::vector<int> foo(myVector);

}

#include "../testStd.hpp"
#include <typeinfo>

void print_map(std::map<int, std::string> map){
    std::map<int, std::string>::iterator it = map.begin();
    std::map<int, std::string>::iterator ite = map.end();
    std::cout << "Content: " << std::endl;
    for(; it != ite; it++){
        std::cout << "Key: " << it->first << " : " << it->second << std::endl;
    }
    std::cout << std::endl;
}

void mapTest(){

        std::cout << " ---------------------------- (0) CONSTRUCTEURS -------------------------------- " << std::endl;
        std::cout << std::endl;
        std::cout << "Contructeur par defaut: " << std::endl;
        std::map<int,std::string> test2;
        std::pair<int, std::string> p0 = std::make_pair(0, "Coucou");
        std::pair<int, std::string> p1 = std::make_pair(1, "comment");
        std::pair<int, std::string> p2 = std::make_pair(2, "ca");
        std::pair<int, std::string> p3 = std::make_pair(3, "va");
        test2.insert(p0);
        test2.insert(p1);
        test2.insert(p2);
        test2.insert(p3);
        
        print_map(test2);

        std::cout << "Contructeur par range d'iterateurs: " << std::endl;
        std::map<int, std::string>::iterator it3 = test2.begin();
        std::map<int, std::string>::iterator ite3 = test2.end();
        std::map<int,std::string> test3(it3, ite3);

        print_map(test3);

        std::cout << "Contructeur par copie: " << std::endl;
        std::map<int,std::string> test(test3);
        print_map(test);

        std::cout << "Operateur =: " << std::endl;
        std::map<int,std::string> test4;
        test4 = test;
        print_map(test4);


        std::cout << std::endl;
        std::cout << " ---------------------------- (1) ITERATEURS -------------------------------- " << std::endl << std::endl;;

        std::map<int, std::string>::iterator it = test4.begin();
        std::cout << "BEGIN: " << std::endl << "Key: " << it->first << " : " << it->second << std::endl << std::endl;
         
        std::map<int, std::string>::iterator ite = test4.end();
        std::cout << "END: " << std::endl; 
        std::cout << "-- sur end: " << std::endl;
        --ite;
        std::cout << "Key: " << ite->first << " : " << ite->second << std::endl << std::endl; 

        std::map<int, std::string>::reverse_iterator rit = test4.rbegin();
        std::map<int, std::string>::reverse_iterator rite = test4.rend();
        std::cout << "RBEGIN: " << std::endl << " Key: " << rit->first << " : " << rit->second << std::endl << std::endl;
        std::cout << "REND: " << std::endl;
        std::cout << "-- sur rend: " << std::endl;
        rite--; 
        std::cout << "Key: " << rite->first << " : " << rite->second << std::endl; 
// test sur const it ?

        std::cout << std::endl << std::endl;
        std::cout << " ---------------------------- (2) CAPACITE -------------------------------- " << std::endl << std::endl;;
        std::map<int,std::string> test5;

        std::cout << "EMPTY : " << std::endl;
        std::cout << "Is test4 empty ? " << test4.empty() << std::endl;
        std::cout << "Is test5 empty ? " << test5.empty() << std::endl;

        std::cout << "SIZE : " << std::endl;
        std::cout << "Size of map test2 : " << test2.size() <<std::endl;
        std::cout << "Size of map test5 : " << test5.size() <<std::endl;

        // std::cout << "MAXSIZE (diff for the nodes used in my RedBlackTree are not the same as the ones used in the std): " << std::endl;
        // std::cout << "Maxsize of map test2 : " << test2.max_size() <<std::endl;


        std::cout << std::endl << std::endl;
        std::cout << " ---------------------------- (3) ELEMENT ACCESS -------------------------------- " << std::endl << std::endl;

        std::cout << "OPERATOR[] : " << std::endl << std::endl;
        std::cout << "Content of test2 : " << std::endl;
        print_map(test2);
        std::cout << "Access key 2 in test2 : " << test2[2] << std::endl;
        std::cout << "Access key 10 in test2 : " << test2[10] << std::endl;
        print_map(test2);

        std::cout << " ---------------------------- (4) MODIFIERS -------------------------------- " << std::endl << std::endl;
        
        std::cout << "INSERT : " << std::endl << std::endl;
        
        std::cout << "- SINGLE ELEMENT : inserting pair(4, \"bien\")" << std::endl;
        std::pair<int, std::string> p4 = std::make_pair(4, "bien");
        std::pair<std::map<int, std::string>::iterator, bool> ret = test2.insert(p4);
        print_map(test2);
        std::cout << std::endl;
        std::cout << "Was the pair unique and inserted ? " << ret.second << std::endl;
        std::cout << "inserting pair(2, \"HELLO\")" << std::endl;
        std::pair<int, std::string> p5 = std::make_pair(2, "HELLO");
        ret = test2.insert(p5);
        print_map(test2);
        std::cout << std::endl;
        std::cout << "Was the pair unique and inserted ? " << ret.second << std::endl;

        std::cout << "RANGE : " << std::endl;
        std::cout << "Is test5 still empty ? " << test5.empty() << std::endl;
        std::cout << "Inserting in test5 : " << std::endl;
        std::map<int, std::string>::iterator it4 = (test2.begin())++;
        std::map<int, std::string>::iterator ite4 = test2.end();
        ite4--;
        test5.insert(it4, ite4);
        print_map(test5);

        std::cout << "ERASE : " << std::endl << std::endl;
        std::cout << "On test5, erase \"comment\" : " << std::endl;
        test5.erase(test5.begin());
        print_map(test5);
        std::cout << "On test5, erase the key 0 (\"ça\") :" << std::endl; 
        size_t retErase = test5.erase(0);
        print_map(test5);
        std::cout << "Number of key erased : " << retErase << std::endl;
        std::cout << "On test5, erase from begin to the end : " << std::endl; 
        test5.erase(test5.begin(), test5.end());
        print_map(test5);

        std::cout << "SWAP : " << std::endl << std::endl;
        std::cout << "Content of test4 :" << std::endl;
        print_map(test4);
        std::cout << "Content of test5 :" << std::endl;
        print_map(test5);
        std::cout << "Swaping test4 and test5" << std::endl;
        test5.swap(test4);
        std::cout << "Content of test4 :" << std::endl;
        print_map(test4);
        std::cout << "Content of test5 :" << std::endl;
        print_map(test5);
        std::cout << "tada" << std::endl;
        
        std::cout << "CLEAR : " << std::endl << std::endl;
        std::cout << "Size of test5 : " << test5.size() << std::endl;
        std::cout << "Clear test5 content" << std::endl;
        test5.clear();
        std::cout << "Size of test5 : " << test5.size() << std::endl;
        std::cout << "Size of test4 : " << test4.size() << std::endl;
        std::cout << "Clear test4 content" << std::endl;
        test4.clear();
        std::cout << "Size of test4 : " << test4.size() << std::endl;
        // print_map(test5);

        std::cout << " ---------------------------- (5) OPERATIONS -------------------------------- " << std::endl << std::endl;
        std::cout << "FIND : " << std::endl << std::endl;
        std::cout << "In test2, find 1 : " << (test2.find(1))->second << std::endl;
        std::cout << "In test2, find 10 : " << (test2.find(10))->second << std::endl; //maybe segfault

        std::cout << "COUNT : " << std::endl << std::endl;
        std::cout << "In test2, count key 1 : " << test2.count(1) << std::endl;
        std::cout << "In test2, count key 100 : " << test2.count(100) << std::endl;

        std::cout << "LOWER BOUND : " << std::endl << std::endl;
        std::cout << "In test2, lowerbound on key 1 : " << (test2.lower_bound(1))->second << std::endl;
        std::cout << "In test2, count key 100 : " << std::endl; //may
        if((test2.lower_bound(100)) == test2.end())
            std::cout << "_end" << std::endl;

        std::cout << "UPPER BOUND : " << std::endl << std::endl;
        std::cout << "In test2, upperbound on key 1 : " << (test2.upper_bound(1))->second << std::endl;
        std::cout << "In test2, upperbound on key 100 : " << std::endl; //may too
        if((test2.upper_bound(100)) == test2.end())
            std::cout << "_end" << std::endl;

        std::cout << "EQUAL RANGE" << std::endl;
        std::pair<std::map<int,std::string>::iterator, std::map<int,std::string>::iterator> retEr;
        retEr = (test2.equal_range(1));
        std::cout << "In test2, equal range on key 1, content of the first pair (same as lowerbound) : " << retEr.first->second << std::endl;
        std::cout << "Content of the second pair (same as upperbound) : " << retEr.second->second << std::endl; // may

        std::cout << " ---------------------------- (6) RELATIONNAL OPERATOR -------------------------------- " << std::endl << std::endl;

        std::map<int, int>	test6;
        std::map<int, int>	test7;
        std::map<int, int>	test8;

        for (int i = 0; i < 20; i++)
            test6.insert(std::make_pair(i, i * i));
        for (int i = 0; i < 20; i++)
            test7.insert(std::make_pair(i, i * i));
        for (int i = 0; i < 100; i++)
            test8.insert(std::make_pair(i, i * i));

        std::cout << "test6 size :" << test6.size() << std::endl;
        std::cout << "test7 size :" << test7.size() << std::endl;
        std::cout << "test8 size :" << test8.size() << std::endl;

        std::cout << "test6 == test7 / test6 == test8 " << std::endl;
        std::cout << (test6 == test7) << "/" << (test6 == test8) << std::endl;

        std::cout << "test6 != test7 / test6 != test8 : " << std::endl;
        std::cout << (test6 != test7) << "/" << (test6 != test8) << std::endl;

        std::cout << "test6 < test7 / test6 < test8 : " << std::endl;
        std::cout << (test6 < test7) << "/" << (test6 < test8) << std::endl;

        std::cout << "test6 <= test7 / test6 <= test8 : " << std::endl;
        std::cout << (test6 <= test7) << "/" << (test6 <= test8) << std::endl;

        std::cout << "test6 > test7 / test6 > test8 : " << std::endl;
        std::cout << (test6 > test7) << "/" << (test6 > test8) << std::endl;

        std::cout << "test6 >= test7 / test6 >= test8 : " << std::endl;
        std::cout << (test6 >= test7) << "/" << (test6 >= test8) << std::endl;

}
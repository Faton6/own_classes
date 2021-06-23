#include <iostream>

#include "Adam_time.h"

int main()
{
    Adam_t test1;
    std::cout << "#############################################\n";
    test1.set_Greg(2021);
    std::cout << "set_Greg(2021)\ttest1 = "<< test1 << '\n';
    std::cout << "#############################################\n";

    Adam_t test2(7528);
    std::cout << "test2(7528)\ttest2 = "<< test2 << '\n';
    std::cout << "get_Greg()\ttest2 = "<< test2.get_Greg() << '\n';
    std::cout << "#############################################\n";

    Adam_t test3(1);
    test2 = test2 + test3;
    std::cout << "test2 = test2 + test3\t:test2 = " << test2 << '\n';
    test2 = test2 - test3;
    std::cout << "test2 = test2 - test3\t:test2 = " << test2 << '\n';
    test2 += test3;
    std::cout << "test2 += test3\t:test2 = " << test2 << '\n';
    test2 -= test3;
    std::cout << "test2 -= test3\t:test2 = " << test2 << '\n';
    std::cout << "#############################################\n";

    Adam_t test4(5,20,14);
    std::cout << "test4(5,20,14)\ttest4 = "<< test4 << '\n';
    std::cout << "get_Greg()\ttest4 = "<< test4.get_Greg() << '\n';
    std::cout << "#############################################\n";
    
    return 0;
}

#include <iostream>
#include "spare_matrix.h"
int main()
{
    SMatrix a;
    std::cin >> a;
    std::cout << "a = \n" << a;
    std::vector<SMatrix::Kof> var = {{1,1,11},{2,2,22},{3,3,33}};
    SMatrix b(var);
    std::cout << "\n############################\n";
    std::cout << "b = \n" << b;
    std::cout << "\n############################\n";
    a.add_val(1,1,33);
    std::cout << "now a = \n" << a;
    std::cout << "\n############################\n";
    a -= b;
    std::cout << "a - b =  \n" << a;
    a += b;
    a = a + b;
    std::cout << "a + b =  \n" << a;
    return 0;
}

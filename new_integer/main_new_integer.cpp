#include <stdexcept>
#include <iostream>
#include <string>
#include <cstdint>


//#include "integer.h"
#include "new_integer.cpp" 


int main()
{
    Integer a(12345);
    std::cout << "################################\n";
    Integer b("100000000000000000");
    std::cout << "b = " << b << '\n';
    Integer c;
    c = a + b;
    std::cout << "a + b = " << c << '\n';

    c = a - b;
    std::cout << "a - b = " << c << '\n';

    a += b;
    std::cout << "a += b\t a = " << a << '\n';

    a -= b;
    std::cout << "a -= b\t a = " << a << '\n';

    a *= b;
    std::cout << "a *= b\t a = " << a << '\n';
    
    a = 100;
    b /= a;
    std::cout << "b /= a\t a = 100, b = " << b << '\n';

    std::cout << "################################\n";

    std::cout << "a == b : " << std::boolalpha << (a == b) << '\n';
    std::cout << "a != b : " << std::boolalpha << (a != b) << '\n';
    std::cout << "a >= b : " << std::boolalpha << (a >= b) << '\n';
    std::cout << "a <= b : " << std::boolalpha << (a <= b) << '\n';
    std::cout << "a > b  : " << std::boolalpha << (a > b) << '\n';
    std::cout << "a < b  : " << std::boolalpha << (a < b) << '\n';
    
    
    std::cout << "################################\n";
    Integer test("123456");
    std::cout << "test = "<< test << '\n';
    std::cout << "\n################################\n\n";
    test.set_num_str("1111111111");
    std::cout << " set_num_str : "<< test << '\n';
    ++test;
    std::cout << "++test = "<< test << '\n';
    --test;
    std::cout << "--test = "<< test << '\n';
    test++;
    std::cout << "test++ = "<< test << '\n';
    test--;
    std::cout << "test-- = "<< test << '\n';

    //std::cout << "################################\n";
    //std::cout << "test = " << (number) << '\n';
    /*
    int64_t a = 120, b = 7, c = 1;
    c = a + b;
    std::cout << "a + b = " << c << '\n';
    c = a - b;
    std::cout << "a - b = " << c << '\n';
    c = a * b;
    std::cout << "a * b = " << c << '\n';
    c = a % b;
    std::cout << "a % b = " << c << '\n';
    c = a / b;
    std::cout << "a / b = " << c << '\n';
    */
    
}

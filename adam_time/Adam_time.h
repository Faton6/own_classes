#ifndef time_Adam_h
#define time_Adam_h

#include <iostream>

#include "ADT.h"

class Adam_t
{
    private:

        static const unsigned int GREG_ADAM_DIFF = 5508;
        static const unsigned int INDICT_SUN_MOON_MAX = 7980;

        unsigned int indict;
        unsigned int sun;
        unsigned int moon;

        unsigned int Adam_year;

        void to_Adam_year();
        void from_Adam_year();

    public:

        Adam_t(){} // пустой конструктор 
        Adam_t(int Adam_year); // конструктор из года от Адама
        Adam_t(int indict, int sun, int moon); // конструктор в год от Адама
        Adam_t(const Adam_t &copy); // констуктор копирования



        int get_Adam_year() const; // Adam_year getter
        void set_Adam_year(int Adam_year); // Adam_year setter

        int get_indict() const; // indict getter

        int get_sun() const; // sun getter

        int get_moon() const; // moon getter

        int get_Greg() const; // Greg_year getter
        void set_Greg(int Greg_year); // Greg_year setter


        Adam_t operator=(const Adam_t &right); // оператор присваивания

        Adam_t operator+(const Adam_t &right) const; // оператор сложения
        Adam_t operator+=(const Adam_t &right); // оператор увеличения числа 

        Adam_t operator-(const Adam_t &right) const; // оператор вычитания
        Adam_t operator-=(const Adam_t &right); // оператор уменьения числа

        const Adam_t operator++();   // префиксный инкремент
        const Adam_t operator++(int);// постфиксный инкремент
        const Adam_t operator--();   // префиксный декремент
        const Adam_t operator--(int);// постфиксный декремент

        friend std::istream &operator>>(std::istream &in, Adam_t &right); // ввод из потока
        friend std::ostream& operator<<(std::ostream& out, const Adam_t &right); // вывод в поток
};

#endif //time_Adam_h

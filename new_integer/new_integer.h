#ifndef new_integer_h
#define new_integer_h

#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include "ADT.h"

class Integer
{
    private:
    
        // разбиение числа
        static const int64_t div_size = 1000000000;
        // хранение числа
        std::vector<int64_t> nums;
        std::string num_str;

        // знак числа
        bool neg;

        // служебные методы:
        std::string pull_str() const; // наполнение строки
        void rm_zero(); // удаляение первых нулей
        void mul_div_size(); // сдвиг разрядов
    
    public:
    
        Integer():neg(false){} // контруктор по умолчанию
        Integer(std::istream &in); // конструктор, принимающий объект istream типа
        Integer(std::string str); // конструктор, принимающий объект string типа
        Integer(int64_t var); // конструктор, принимающий объект int64_t типа
        Integer(const Integer &copy); // конструктор копирования
        //~Integer() = default;
        ~Integer(){}
        std::string get_num_str() const { return this->num_str; } // getter
        void set_num_str(std::string num_str); // setter

        Integer &operator=(const Integer &right); // оператор присваивания
        Integer &operator=(std::string right); // оператор присваивания
        Integer &operator=(int64_t right); // оператор присваивания
        
        const Integer operator+() const; // обеспечение арифметики
        const Integer operator-() const; // обеспечение арифметики

        friend const Integer operator+(Integer left, const Integer &right); // оператор сложения
        Integer &operator+=(const Integer &right); // оператор увеличения числа 

        friend const Integer operator-(Integer left, const Integer &right); // оператор вычитания
        Integer &operator-=(const Integer &right); // оператор уменьения числа

        const Integer operator++();   // префиксный инкремент
        const Integer operator++(int);// постфиксный инкремент
        const Integer operator--();   // префиксный декремент
        const Integer operator--(int);// постфиксный декремент

        friend const Integer operator*(const Integer &left, const Integer &right); // оператор умножения
        Integer &operator*=(const Integer &right); // оператор умножения числа

        friend const Integer operator/(const Integer &left, const Integer &right); // оператор деления
        Integer &operator /=(const Integer &right); // оператор деления числа

        friend std::istream &operator>>(std::istream &in, Integer &right); // ввод из потока
        friend std::ostream &operator<<(std::ostream& out, const Integer& right); // вывод в поток

        friend bool operator==(const Integer &left, const Integer &right); // оператор сравнения на равенство
        friend bool operator<(const Integer &left, const Integer &right);  // оператор меньше
        friend bool operator!=(const Integer &left, const Integer &right); // оператор не равно
        friend bool operator<=(const Integer &left, const Integer &right); // оператор меньше либо равно
        friend bool operator>(const Integer &left, const Integer &right);  // оператор больше
        friend bool operator>=(const Integer &left, const Integer &right); // оператор больше либо равно

        operator std::string(); // оператор приведения к string
        //operator Integer(){return *this;}
};

#endif //new_integer_h

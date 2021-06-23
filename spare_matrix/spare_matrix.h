#ifndef matrix_h
#define matrix_h

#include <iostream>
#include <vector>

#include "ADT.h"

// Разреженная матрица, представленная динамическим 
// массивом структур, содержащих описания ненулевых коэффициентов: индексы 
// местоположения коэффициента в матрице (целые) и значение коэффициента (вещественное


class SMatrix : public ADT
{
    public:
        struct Kof
        {
            size_t x = 0;
            size_t y = 0;
            double value = 0.0;
            Kof(){}
            Kof(int x, int y, double value) : 
            x(x), y(y), value(value){}
            Kof(const Kof &right) :
            x(right.x), y(right.y), value(right.value){}
            ~Kof(){}
        };
    private:
        size_t rows = 1;
        size_t cols = 1;
        std::vector<Kof> full;

    public:
        SMatrix(){}
        SMatrix(std::istream &in);
        SMatrix(Kof *a, size_t size);
        SMatrix(std::vector<Kof> &a);
        SMatrix(const SMatrix &right); // copy constructor
        ~SMatrix(){}
        
        std::ostream & writeSMatrix(std::ostream &out = std::cout) const;
        void add_kof(Kof a);
        void add_val(int x, int y, double value);
        void set_val(int x, int y, double value);
        double get_val(int x, int y);

        SMatrix operator=(const SMatrix & right) ;
        SMatrix operator+=(const SMatrix & right);
        SMatrix operator-=(const SMatrix & right);
        SMatrix operator+(const SMatrix & right) const;
        SMatrix operator-(const SMatrix & right) const;

        friend std::ostream & operator<< (std::ostream &left, const SMatrix &right);
        friend std::istream & operator>> (std::istream &left, SMatrix &right);
        std::ostream &print(std::ostream &out) const override { return out << *this; } 
};

#endif // matrix_h

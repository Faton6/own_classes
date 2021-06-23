#include <iostream>
#include <algorithm>

#include "spare_matrix.h"

SMatrix::SMatrix(std::istream &in ) {
    full.reserve(4);
    int x = 0;
    int y = 0;
    double var = 0;
    do
    {
        in >> x;
        if (!x) break;
        if (x > this->rows) this->rows = x;

        in >> y;
        if (!y) break;
        if (y > this->cols) this->cols = y;

        in >> var;
        if ( var <= 0 + 0.001 && var >= 0 - 0.001 ) continue;

        Kof a(x,y,var);
        full.push_back(a);
        
    } while ( x && y && full.size() < 10000);
}

SMatrix::SMatrix(const SMatrix &right)
{
    this->rows = right.rows;
    this->cols = right.cols;
    this->full = right.full;
}

SMatrix::SMatrix(Kof *a, size_t size) 
{
    full.reserve(size);
    for(size_t i = 0; i < size; ++i) this->add_kof(a[i]);
}

SMatrix::SMatrix(std::vector<Kof> &a)
{
    full = a;
    for(size_t i = 0; i < full.size(); ++i)
    {
        if(full[i].x > this->rows) this->rows = full[i].x;
        if(full[i].y > this->cols) this->cols = full[i].y;
    }
}

std::ostream & SMatrix::writeSMatrix(std::ostream &out ) const
{ 
    bool flg = false;
    for(size_t i = 1; i < this->rows+1; ++i)
    {
        for(size_t j = 1; j < this->cols+1; ++j) 
        {
            for(size_t k = 0; k < full.size(); ++k)
            {
                if (full[k].x == i && full[k].y == j) 
                {
                    out << full[k].value << ' '; 
                    flg = true;
                    break;
                }
            }
            if (!flg)
            {
                out << 0.0 << ' ';
            }
            flg = false;
        }
        out << '\n';
    }
    return out;
}

void SMatrix::add_kof(Kof a)
{
    this->full.push_back(a);
    if(full[full.size()-1].x > this->rows) this->rows = full[full.size()-1].x;
    if(full[full.size()-1].y > this->cols) this->cols = full[full.size()-1].y;
}

void SMatrix::add_val(int x, int y, double value)
{
    Kof a(x,y,value);
    this->full.push_back(a);
    if(full[full.size()-1].x > this->rows) this->rows = full[full.size()-1].x;
    if(full[full.size()-1].y > this->cols) this->cols = full[full.size()-1].y;
}

void SMatrix::set_val(int x, int y, double value)
{
    for(size_t i = 0; i < full.size(); ++i)
    {
        if(full[i].x == x && full[i].y == y) 
        {
            full[i].value = value;
            return;
        }
    }
    this->add_val(x,y,value);
}

SMatrix SMatrix::operator=(const SMatrix & right)
{
    this->rows = right.rows;
    this->cols = right.cols;
    this->full = right.full;
    return *this;
}
SMatrix SMatrix::operator+(const SMatrix & right) const
{
    SMatrix var(*this);
    var.rows = std::max(this->rows, right.rows);
    var.cols = std::max(this->cols, right.cols);
    bool flg = true;
    for(size_t i = 0; i < right.full.size(); ++i)
    {
        for(size_t j = 0; j < this->full.size(); ++j)
        {
            if(right.full[i].x == var.full[j].x &&
               right.full[i].y == var.full[j].y)
               {
                   var.full[j].value += right.full[i].value;
                   flg = false;
                   break;
               }
        }
        if (flg) var.full.push_back(right.full[i]); 
        flg = true;
    }
    return var;
}
SMatrix SMatrix::operator+=(const SMatrix & right)
{
    *this = this->operator+(right);
    return *this;
}
SMatrix SMatrix::operator-(const SMatrix & right) const
{
    SMatrix var(*this);
    var.rows = std::max(this->rows, right.rows);
    var.cols = std::max(this->cols, right.cols);
    bool flg = true;
    for(size_t i = 0; i < right.full.size(); ++i)
    {
        for(size_t j = 0; j < this->full.size(); ++j)
        {
            if(right.full[i].x == var.full[j].x &&
               right.full[i].y == var.full[j].y)
               {
                   var.full[j].value -= right.full[i].value;
                   flg = false;
                   break;
               }
        }
        if (flg) 
        {
            var.full.push_back(right.full[i]);
            var.full[var.full.size()-1].value -= 2 * var.full[var.full.size()-1].value;
        }
        flg = true;
    }
    return var;
}
SMatrix SMatrix::operator-=(const SMatrix & right)
{
    *this = this->operator-(right);
    return *this;
}

std::ostream & operator<< (std::ostream &out, const SMatrix &right)
{
    return right.writeSMatrix(out);
}

std::istream & operator>> (std::istream &left, SMatrix &right)
{
    SMatrix a(left);
    right = a;
    return left;
}

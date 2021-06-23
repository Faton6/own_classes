#include "Adam_time.h"

//в год от Адама
void Adam_t::to_Adam_year()
{
    for(size_t year = 1; year < INDICT_SUN_MOON_MAX; ++year)                                           
    {     
        Adam_t var(year);                                                                   
        if (var.indict % 15 == this->indict && var.sun % 28 == this->sun && var.moon % 19 == this->moon)
        {                
            this->Adam_year = var.Adam_year;
        }                                                                       
    }
}
// из года от Адама
void Adam_t::from_Adam_year()
{
    if (!(this->Adam_year % 15)) this->indict = 15;
    else this->indict = this->Adam_year % 15;

    if (!(this->Adam_year % 28)) this->sun = 28;
    else this->sun = this->Adam_year % 28;

    if (!(this->Adam_year % 19)) this->moon = 19;
    else this->moon = this->Adam_year % 19;
}

// конструктор из года от Адама
Adam_t::Adam_t(int Adam_year) : Adam_year(Adam_year)
{
    from_Adam_year();
}

// конструктор в год от Адама
Adam_t::Adam_t(int indict, int sun, int moon) : indict(indict), sun(sun), moon(moon)
{
    to_Adam_year();
}

// констуктор копирования
Adam_t::Adam_t(const Adam_t &copy)
{
    this->Adam_year = copy.Adam_year;
    this->indict = copy.indict;
    this->sun = copy.sun;
    this->moon = copy.moon;
}

// Adam_year getter
int Adam_t::get_Adam_year() const { return this->Adam_year; } 

// Adam_year setter
void Adam_t::set_Adam_year(int Adam_year)
{
    Adam_t var(Adam_year);
    *this = var;
}

// indict getter
int Adam_t::get_indict() const { return this->indict; } 

// sun getter
int Adam_t::get_sun() const { return this->sun; } 

// moon getter
int Adam_t::get_moon() const { return this->moon; } 

// Greg_year getter
int Adam_t::get_Greg() const 
{
    return this->Adam_year - GREG_ADAM_DIFF;
}

// Greg_year setter
void Adam_t::set_Greg(int Greg_year) 
{
    this->Adam_year = Greg_year + GREG_ADAM_DIFF;
    from_Adam_year();
}

// оператор присваивания
Adam_t Adam_t::operator=(const Adam_t &right) 
{
    this->indict = right.indict;
    this->sun = right.sun;
    this->moon = right.moon;
    this->Adam_year = right.Adam_year;
    return *this;
}

// оператор сложения
Adam_t Adam_t::operator+(const Adam_t &right) const 
{
    Adam_t var(*this);
    var.Adam_year += right.Adam_year;
    if (this->Adam_year > INDICT_SUN_MOON_MAX) std::runtime_error( "Error: overflow Adams time!" );
    var.from_Adam_year();
    return var;
}

// оператор увеличения числа 
Adam_t Adam_t::operator+=(const Adam_t &right)
{
    *this = *this + right;
    return *this;
}

// оператор вычитания
Adam_t Adam_t::operator-(const Adam_t &right) const
{
    Adam_t var(*this);
    var.Adam_year -= right.Adam_year;
    if (this->Adam_year < 0) throw "Error: minus Adams time!";
    var.from_Adam_year();
    return var;
}

// оператор уменьения числа
Adam_t Adam_t::operator-=(const Adam_t &right) 
{
    *this = *this - right;
    return *this;
}

// префиксный инкремент
const Adam_t Adam_t::operator++() 
{
    *this += 1;
    return *this;
}
 
// постфиксный инкремент
const Adam_t Adam_t::operator++(int) 
{
    *this += 1;
    return (*this - 1);
}
 
// префиксный декремент
const Adam_t Adam_t::operator--()
{
    *this -= 1;
    return *this;
}
 
// постфиксный декремент
const Adam_t Adam_t::operator--(int) 
{
    *this -= 1;
    return (*this + 1);
}

// вывод из потока
std::istream &operator>>(std::istream &in, Adam_t &right)
{
    in >> right.Adam_year;
    right.from_Adam_year();
    return in;
}

// ввод в поток
std::ostream& operator<<(std::ostream& out, const Adam_t &right)
{
    return out << right.Adam_year;
}

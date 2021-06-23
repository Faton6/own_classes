#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>

#include "new_integer.h"

// конструктор, принимающий объект istream типа
Integer::Integer(std::istream &in)
{
    std::string num_str;
    in >> num_str;
    this->num_str = num_str;
    if (num_str.length() == 0) this->neg = false;
    else 
    {
        if (num_str[0] == '-') 
        {
			num_str = num_str.substr(1);
		    this->neg = true;
		} 
        else this->neg = false;

        for (int64_t i = num_str.length(); i > 0; i -= 9) 
        {
            if (i < 9)
                this->nums.push_back(std::atoi(num_str.substr(0, i).c_str()));
            else
                this->nums.push_back(std::atoi(num_str.substr(i - 9, 9).c_str()));
        }
        
        this->rm_zero();   
    }
}

// конструктор, принимающий объект string типа
Integer::Integer(std::string num_str) : num_str(num_str)
{
    if (num_str.length() == 0) this->neg = false;
    else 
    {
        if (num_str[0] == '-') 
        {
            this->neg = true;
			num_str = num_str.substr(1);
		} 
        else this->neg = false;

        for (int64_t i = num_str.length(); i > 0; i -= 9) 
        {
            if (i < 9)
                this->nums.push_back(std::atoi(num_str.substr(0, i).c_str()));
            else
                this->nums.push_back(std::atoi(num_str.substr(i - 9, 9).c_str()));
        }
        
        this->rm_zero();   
        
    }
}

// конструктор, принимающий объект int64_t типа
Integer::Integer(int64_t var) 
{
    this->num_str = std::to_string(var);
    if (var < 0) 
    {
        this->neg = true;
        var -= 2 * var;
    }
    else this->neg = false;
    do 
    {
        this->nums.push_back(var % Integer::div_size);
        var /= Integer::div_size;
    } while (var != 0);
}

// конструктор копирования
Integer::Integer(const Integer &copy) : 
    nums(copy.nums), num_str(copy.num_str), neg(copy.neg){}

// setter
void Integer::set_num_str(std::string num_str)
{
    this->num_str = num_str;
    Integer var(num_str);
    *this = var;
}

// оператор присваивания
Integer &Integer::operator=(const Integer &right)
{
    this->nums = right.nums;
    this->neg = right.neg;
    this->num_str = this->pull_str();
    return *this;
}

// оператор присваивания
Integer &Integer::operator=(std::string right)
{
    Integer var(right);
    return *this = var;
}

// оператор присваивания
Integer &Integer::operator=(int64_t right)
{
    Integer var(right);
    return *this = var;
}
 
// обеспечение арифметики
const Integer Integer::operator+() const { return Integer(*this); }
 
// обеспечение арифметики
const Integer Integer::operator-() const 
{
	Integer copy(*this);
	copy.neg = !copy.neg;
	return copy;
}

// оператор сложения
const Integer operator+(Integer left, const Integer &right)
{
    if (left.neg) 
    {
		if (right.neg) return -(-left + (-right));
		else return right - (-left);
	}
    else if (right.neg) return left - (-right);
    int var = 0; // переполнение
    for (size_t i = 0; i < std::max(left.nums.size(), right.nums.size()) || var != 0; ++i) 
    {
        if (i == left.nums.size()) left.nums.push_back(0);

        if (i < right.nums.size()) left.nums[i] += var + right.nums[i];
        else left.nums[i] += var;

        if (left.nums[i] >= Integer::div_size) {left.nums[i] -= Integer::div_size; var = 1;}
        else var = 0;
    }
    return left;
}

// оператор увеличения числа 
Integer &Integer::operator+=(const Integer &right) { return *this = (*this + right);}
 
// оператор вычитания
const Integer operator-(Integer left, const Integer &right)
{
    
    if (right.neg) return left + (-right);
	else if (left.neg) return -(-left + right);
	else if (left < right) return -(right - left);
    
    int var = 0;
    for (size_t i = 0; i < right.nums.size() || var != 0; ++i) 
    {
        if (i < right.nums.size()) left.nums[i] -= var + right.nums[i];
        else left.nums[i] -= var;
        var = left.nums[i] < 0;
        if (var != 0) left.nums[i] += Integer::div_size;
    }
    
    left.rm_zero();
    return left;
}
 
// оператор уменьения числа
Integer &Integer::operator -=(const Integer &right) {
    return *this = (*this - right);
}

// префиксный инкремент
const Integer Integer::operator++() 
{
    *this += 1;
    return *this;
}
 
// постфиксный инкремент
const Integer Integer::operator++(int) 
{
    *this += 1;
    return (*this - 1);
}
 
// префиксный декремент
const Integer Integer::operator--()
{
    *this -= 1;
    return *this;
}
 
// постфиксный декремент
const Integer Integer::operator--(int) 
{
    *this -= 1;
    return (*this + 1);
}

// оператор умножения
const Integer operator*(const Integer &left, const Integer &right) 
{
	Integer result;
	result.nums.resize(left.nums.size() + right.nums.size());
    int64_t qwa = 0;
    size_t var = 0;
	for (size_t i = 0; i < left.nums.size(); ++i) 
    {
		for (size_t j = 0; j < right.nums.size() || var != 0; ++j) 
        {
            if (j < right.nums.size())
            {
                qwa =  result.nums[i + j] + 
				left.nums[i] * right.nums[j] + var;
            }
            else qwa = result.nums[i + j] +var;
			result.nums[i + j] = static_cast<int>(qwa % Integer::div_size);
			var = static_cast<size_t>(qwa / Integer::div_size);
            qwa = 0;
		}
        var = 0;
	}
    if (left.neg == right.neg) result.neg = false;
    else result.neg = true;
	result.rm_zero();
	return result;
}

// оператор умножения числа
Integer &Integer::operator*=(const Integer &right) { return *this = (*this * right); }

// сдвиг разрядов
void Integer::mul_div_size() 
{
	if (this->nums.size() == 0) 
    {
		this->nums.push_back(0);
		return;
	}
	this->nums.push_back( this->nums[this->nums.size() - 1] );
	for (size_t i = this->nums.size() - 2; i > 0; --i) this->nums[i] = this->nums[i - 1];
	this->nums[0] = 0;
}

// оператор деления
const Integer operator/(const Integer &left, const Integer &right) 
{
	if (right == 0) throw "Error: division by zero!";
	Integer qwa(right);
	qwa.neg = false;
	Integer var, result;
	result.nums.resize(left.nums.size());
	for (int64_t i = left.nums.size() - 1; i >= 0; --i) 
    {
		var.mul_div_size();
		var.nums[0] = left.nums[i];
		var.rm_zero();
		int x = 0, y = 0, z = Integer::div_size;
		while (y <= z) 
        {
			int s = (y + z) / 2;
			Integer a = qwa * s;
			if (a <= var) 
            {
				x = s;
				y = s + 1;
			}
			else z = s - 1;
		}
		result.nums[i] = x;
		var = var - qwa * x;
	}

	result.neg = left.neg != right.neg;
	result.rm_zero();
	return result;
}

// оператор деления числа
Integer &Integer::operator/=(const Integer &right) { return *this = (*this / right); }

// вывод в поток
std::ostream& operator<<(std::ostream& out, const Integer& right) 
{
    return out << right.num_str;
}

// ввод из потока
std::istream& operator>>(std::istream &in, Integer &right) 
{
    Integer var(in);
    right = var;
    return in;
}

// оператор сравнения на равенство
bool operator==(const Integer &left, const Integer &right)
{
    if (left.neg != right.neg) return false;
    if (left.nums.empty()) 
    {
        if (right.nums.empty() || (right.nums.size() == 1 && right.nums[0] == 0)) return true;
        else return false;
    }
    
    if (right.nums.empty()) 
    {
        if ( left.nums[0] == 0 && left.nums.size() == 1) return true;
        else return false;
    }
 
    if (left.nums.size() != right.nums.size()) return false;
    for (size_t i = 0; i < left.nums.size(); ++i) if (left.nums[i] != right.nums[i]) return false;
 
    return true;
}
 
// оператор меньше
bool operator<(const Integer &left, const Integer &right) 
{
    if (left == right) return false;
    if (left.neg) 
    {
        if (right.neg) return ((-right) < (-left));
        else return true;
    }
    else if (right.neg) return false;
    else 
    {
        if (left.nums.size() != right.nums.size()) return left.nums.size() < right.nums.size();
        else 
        {
            for (size_t i = left.nums.size() - 1; i >= 0; --i) 
            {
                if (left.nums[i] != right.nums[i]) return left.nums[i] < right.nums[i];
            }
            return false;
        }
    }
}
 
// оператор не равно
bool operator!=(const Integer &left, const Integer &right) 
{
    return !(left == right);
}
 
// оператор меньше либо равно
bool operator<=(const Integer &left, const Integer &right) 
{
    return (left < right || left == right);
}
 
// оператор больше
bool operator>(const Integer &left, const Integer &right) 
{
    return !(left <= right);
}
 
// оператор больше либо равно
bool operator>=(const Integer &left, const Integer &right) 
{
    return !(left < right);
}

// оператор приведения к string
Integer::operator std::string()
{
    this->num_str = this->pull_str();
    return this->num_str; 
}


// служебные функции:

// наполнение строки
std::string Integer::pull_str() const
{
    if (this->nums.empty()) return "0";
    else 
    {
        std::stringstream var;
        if (this->neg) var << '-';
        var << this->nums.back();
        for (int64_t i = this->nums.size() - 2; i >= 0; --i)
            {  var << this->nums[i]; }
        std::string qwa;
        var >> qwa;
        return qwa;
    }
    
}

// удаляение первых нулей
void Integer::rm_zero() 
{
    while (this->nums.size() > 1 && this->nums.back() == 0) this->nums.pop_back();
    if (this->nums.size() == 1 && this->nums[0] == 0) this->neg = false;
}

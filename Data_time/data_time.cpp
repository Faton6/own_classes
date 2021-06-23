#include <ctime>
#include "data_time.h"

Unix_t::Unix_t() : 
utime(0), unix_t(0), info(std::localtime(&utime)), year(0),
month(0), day(0), min(0), sec(0) {}

Unix_t::Unix_t(uint64_t unix_t) : utime(unix_t), unix_t(unix_t)
{
    info = std::localtime(&utime);
    this->year  = info->tm_year + 1900;
    this->month = info->tm_mon + 1;
    this->day   = info->tm_mday;
    this->hour  = info->tm_hour;
    this->min   = info->tm_min;
    this->sec   = info->tm_sec;
}
Unix_t::Unix_t(int year, int month, int day, int hour, int min, int sec)
{
    this->year  = year;
    this->month = month;
    this->day   = day;
    this->hour  = hour;
    this->min   = min;
    this->sec   = sec;
    time(&utime);
    info = localtime(&utime);
    info->tm_year = year - 1900;
    info->tm_mon  = month - 1;
    info->tm_mday = day;
    info->tm_hour = hour;
    info->tm_min  = min;
    info->tm_sec  = sec;
    utime = mktime(info);
    unix_t = utime;
}

Unix_t::Unix_t(const Unix_t &right) :
utime(right.utime), unix_t(right.unix_t),
year(right.year), month(right.month), day(right.day),
hour(right.hour), min(right.min), sec(right.sec) {}

Unix_t Unix_t::operator=(const Unix_t &right)
{
    this->utime  = right.utime;
    this->unix_t = right.unix_t;
    this->year = right.year;
    this->month= right.month;
    this->day  = right.day;
    this->hour = right.hour;
    this->min  = right.min;
    this->sec  = right.sec;
    return *this;
}
Unix_t Unix_t::operator+(const Unix_t &right) const
{
    Unix_t var(*this);
    var.utime  += right.utime;
    var.unix_t += right.unix_t;
    var.year += right.year;
    var.month+= right.month;
    var.day  += right.day;
    var.hour += right.hour;
    var.min  += right.min;
    var.sec  += right.sec;
    return var;
}
Unix_t Unix_t::operator-(const Unix_t &right) const
{
    Unix_t var(*this);
    var.utime  -= right.utime;
    var.unix_t -= right.unix_t;
    var.year -= right.year;
    var.month-= right.month;
    var.day  -= right.day;
    var.hour -= right.hour;
    var.min  -= right.min;
    var.sec  -= right.sec;
    return var;
}
Unix_t Unix_t::operator+=(const Unix_t &right)
{
    *this = this->operator+(right);
    return *this;
}
Unix_t Unix_t::operator-=(const Unix_t &right)
{
    *this = this->operator-(right);
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Unix_t &right)
{
    return out << right.get_time();
}
std::istream &operator>>(std::istream &in, Unix_t &right)
{
    uint64_t var;
    in >> var;
    Unix_t qwa(var);
    right = qwa;
    return in;
}

bool operator< (const Unix_t &left, const Unix_t &right)
{
    return left.unix_t < right.unix_t ? true : false;
}
bool operator<=(const Unix_t &left, const Unix_t &right)
{
    return left.unix_t <= right.unix_t ? true : false;
}
bool operator> (const Unix_t &left, const Unix_t &right)
{
    return left.unix_t > right.unix_t ? true : false;
}
bool operator>=(const Unix_t &left, const Unix_t &right)
{
    return left.unix_t >= right.unix_t ? true : false;
}
bool operator==(const Unix_t &left, const Unix_t &right)
{
    return left.unix_t == right.unix_t ? true : false;
}
bool operator!=(const Unix_t &left, const Unix_t &right)
{
    return left.unix_t != right.unix_t ? true : false;
}

void Unix_t::set_utime(uint64_t unix_t)
{
    this->unix_t = unix_t;
    utime = unix_t;
}

char* Unix_t::get_actuall_time() const
{
    Unix_t var(std::time(nullptr));
    return std::ctime(&utime);
}

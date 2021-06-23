#ifndef data_time_h // если не объвлен
#define data_time_h // объявление

// подключение необходимых заголовочных файлов
#include <cstdint> 
#include <ctime>
#include <iostream>

#include "ADT.h"

// объявление макросов подстановки
#define WINDOWS_TICK 10000000       // 100 ms
#define EPOCH_DIFFER 11644473600LL  // unix time - win time


class Unix_t
{
    private:
        std::time_t utime; // для работы с методами класса time_t
        uint64_t unix_t; // секунд от 00:00 1 января 1970 года
        struct tm *info; // для работы с годом, месяцем, днём, часом, минутой и секундой

        int year; // хранение года
        int month;// хранение месяца
        int day;  // хранение дня
        int hour; // хранение часа
        int min;  // хранение минуты
        int sec;  // хранение секунды
    
    public:
        Unix_t(); // конструктор класса
        Unix_t(uint64_t unix_t); // конструктор класса
        Unix_t(int year, int month, int day=1, int hour=0, int min=0, int sec=0); // конструктор класса
        Unix_t(const Unix_t &right); // конструктор копирования
        ~Unix_t() {}  // деструктор класса

        // операторы приведения типов
        operator std::time_t() const { return unix_t; }
        operator uint64_t() const { return utime; }

        uint64_t winT_to_unixT() // преобразование из формат представления filetime 
        {
            return ( (this->unix_t / WINDOWS_TICK) - EPOCH_DIFFER);
        }
        uint64_t unixT_to_winY() // преобразование в формат представления filetime 
        {
            return (WINDOWS_TICK * (EPOCH_DIFFER + this->unix_t) );
        }

        // акцессоры
        void set_utime(uint64_t unix_t);
        void set_year(int year) { this->year = year; }
        void set_month(int month) { this->month = month; }
        void set_day(int day) { this->day = day; }
        void set_hour(int hour) { this->hour = hour; }
        void set_min(int min) { this->min = min; }
        void set_sec(int sec) { this->sec = sec; }  
        int get_year() { return this->year; }
        int get_month() { return this->month; }
        int get_day() { return this->day; }
        int get_hour() { return this->hour; }
        int get_min() { return this->min; }
        int get_sec() { return this->sec; }

        char* get_time() const { return std::ctime(&utime); }  // метод, возвращающий время в человеко-читаемом формате
        char* get_actuall_time() const; // метод, возвращающий актуальное время в человеко-читаемом формате
        uint64_t get_utime() const { return unix_t; } // метод, возвращающий время в Unix формате
        

        // перегрузка арифметических операторов
        Unix_t operator=(const Unix_t &right);
        Unix_t operator+(const Unix_t &right) const;
        Unix_t operator-(const Unix_t &right) const;
        Unix_t operator+=(const Unix_t &right);
        Unix_t operator-=(const Unix_t &right);

        // перегрузка дружественной функцией операторов вввода/вывода в поток
        friend std::ostream & operator<<(std::ostream &out, const Unix_t &right);
        friend std::istream & operator>>(std::istream &in, Unix_t &right);

        // перегрузка дружественной функцией операторов сравнения
        friend bool operator< (const Unix_t &left, const Unix_t &right);
        friend bool operator<=(const Unix_t &left, const Unix_t &right);
        friend bool operator> (const Unix_t &left, const Unix_t &right);
        friend bool operator>=(const Unix_t &left, const Unix_t &right);
        friend bool operator==(const Unix_t &left, const Unix_t &right);
        friend bool operator!=(const Unix_t &left, const Unix_t &right);
};
#endif // data_time

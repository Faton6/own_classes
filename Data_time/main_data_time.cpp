#include <iostream>
#include <ctime>
#include "data_time.h"
//#include <string> // for test commit

int main() {

    // тест конструктора по умолчанию
    Unix_t now;
    std::cout << now.get_time();

    // тест конструктора со входом unix time
    std::cout << "################################\n\n";

    uint64_t heh = 1618000095;
    Unix_t tmp(heh);
    std:: cout << tmp.get_time();
    std::cout << "Year" << tmp.get_year()<<std::endl;
    std::cout << "Month: "<< tmp.get_month()<< std::endl;
    std::cout << "Day: "<<  tmp.get_day() << std::endl;
    std::cout << "Time: "<<  tmp.get_hour() << ":";
    std::cout <<  tmp.get_min() << ":";
    std::cout <<  tmp.get_sec() << std::endl;
    std::cout << "unix time: "<< tmp.get_utime() << std::endl;
    std::cout << "################################\n\n";

    // тест конструктора со входом 
    //года, месяца, дня, часа, минуты, секунды
    Unix_t mp(now);
    std:: cout << mp;
    mp -= now;
    std:: cout << mp.get_time();

    // сверка времени
    std::cout << "################################\n\n";
    std::time_t til = std::time(nullptr);
    std::cout << std::asctime(std::localtime(&til)) << "tmp = " << til << '\n';
    
}

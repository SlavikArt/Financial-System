#pragma once
#include <iostream>
#include <sstream>
#include <chrono>
#include <string>
#include "functions.h"

class Date
{
	unsigned day;
	unsigned month;
	unsigned year;
public:
    Date(unsigned num);
    Date(unsigned day, unsigned month, unsigned year);

    unsigned getDay() const;
    unsigned getMonth() const;
    unsigned getYear() const;

    void setDay(unsigned day);
    void setMonth(unsigned month);
    void setYear(unsigned year);

    bool operator==(const Date& right) const;
    bool operator!=(const Date& right) const;

    std::string ToString();

    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    Date operator-(int days) const;
};

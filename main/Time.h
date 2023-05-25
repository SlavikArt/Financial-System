#pragma once
#include <iostream>
#include <sstream>
#include <chrono>
#include <string>

class Time
{
    unsigned hour;
    unsigned minute;
    unsigned second;
public:
    Time(unsigned num);
    Time(unsigned hour, unsigned minute, unsigned second);

    unsigned getHour() const;
    unsigned getMinute() const;
    unsigned getSecond() const;

    void setHour(unsigned hour);
    void setMinute(unsigned minute);
    void setSecond(unsigned second);

    bool operator==(const Time& right) const;
    bool operator!=(const Time& right) const;

    std::string ToString();

    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};

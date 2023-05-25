#include "Date.h"

int toJulian(const Date& date)
{
    int a = floor((14 - date.getMonth()) / 12);
    int y = date.getYear() + 4800 - a;
    int m = date.getMonth() + 12 * a - 3;
    return date.getDay() + floor((153 * m + 2) / 5) + 365 * y + floor(y / 4) - floor(y / 100) + floor(y / 400) - 32045;
}

int dateDifference(const Date& date1, const Date& date2)
{
    return toJulian(date2) - toJulian(date1);
}

Date fromJulian(int julian)
{
    int y = 4716, v = 3, j = 1401, u = 5, m = 2, s = 153, n = 12, w = 2, r = 4, B = 274277, p = 1461, C = -38;
    int f = julian + j + (((4 * julian + B) / 146097) * 3) / 4 + C;
    int e = r * f + v;
    int g = (e % p) / r;
    int h = u * g + w;
    int D = (h % s) / u + 1;
    int M = ((h / s + m) % n) + 1;
    int Y = (e / p) - y + (n + m - M) / n;
    return Date(D, M, Y);
}

Date::Date(unsigned num)
{
    const auto now = std::chrono::system_clock::now();
    const auto in_time_t = std::chrono::system_clock::to_time_t(now);

    struct tm time_info;
    const auto errno_value = localtime_s(&time_info, &in_time_t);
    if (errno_value != 0)
    {
        throw std::runtime_error("localtime_s() failed: " + std::to_string(errno_value));
    }
    this->day = time_info.tm_mday;
    this->month = time_info.tm_mon + 1;
    this->year = time_info.tm_year + 1900;
}

Date::Date(unsigned day, unsigned month, unsigned year) 
    : day(day), month(month), year(year) {}

unsigned Date::getDay() const
{
    return day;
}

unsigned Date::getMonth() const
{
    return month;
}

unsigned Date::getYear() const
{
    return year;
}

void Date::setDay(unsigned day)
{
    this->day = day;
}

void Date::setMonth(unsigned month)
{
    this->month = month;
}

void Date::setYear(unsigned year)
{
    this->year = year;
}

bool Date::operator==(const Date& right) const
{
    return (day == right.day 
        && month == right.month 
        && year == right.year);
}

bool Date::operator!=(const Date& right) const
{
    return !(*this == right);
}

std::string Date::ToString()
{
    std::stringstream s;
    s << day << '-' << month << '-' << year;
    return s.str();
}

Date Date::operator-(int days) const
{
    int julian = toJulian(*this);
    return fromJulian(julian - days);
}
std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.day << '-' << date.month << '-' << date.year;
    return os;
}

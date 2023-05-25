#include "Time.h"

Time::Time(unsigned num)
{
    const auto now = std::chrono::system_clock::now();
    const auto in_time_t = std::chrono::system_clock::to_time_t(now);

    struct tm time_info;
    const auto errno_value = localtime_s(&time_info, &in_time_t);
    if (errno_value != 0)
    {
        throw std::runtime_error("localtime_s() failed: " + std::to_string(errno_value));
    }
    this->hour = time_info.tm_hour;
    this->minute = time_info.tm_min;
    this->second = time_info.tm_sec;
}

Time::Time(unsigned hour, unsigned minute, unsigned second) 
    : hour(hour), minute(minute), second(second) {}

unsigned Time::getHour() const
{
    return hour;
}

unsigned Time::getMinute() const
{
    return minute;
}

unsigned Time::getSecond() const
{
    return second;
}

void Time::setHour(unsigned hour)
{
    this->hour = hour;
}

void Time::setMinute(unsigned minute)
{
    this->minute = minute;
}

void Time::setSecond(unsigned second)
{
    this->second = second;
}

bool Time::operator==(const Time& other) const
{
    return (hour == other.hour 
        && minute == other.minute 
        && second == other.second);
}

bool Time::operator!=(const Time& other) const
{
    return !(*this == other);
}

std::string Time::ToString()
{
    std::stringstream s;
    s << hour << '-' << minute << '-' << second;
    return s.str();
}

std::ostream& operator<<(std::ostream& os, const Time& time)
{
    os << time.hour << '-' << time.minute << '-' << time.second;
    return os;
}

#pragma once
#include <iostream>
#include <sstream>
#include "Date.h"

inline std::string center(const std::string s, const int w)
{
    std::stringstream ss, spaces;
    int padding = w - s.size();                 // count excess room to pad
    for (int i = 0; i < padding / 2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();    // format with padding
    if (padding > 0 && padding % 2 != 0)               // if odd #, add 1 space
        ss << " ";
    return ss.str();
}


#include "colortext.hpp"
#include <string>

std::string SetColor(std::string color, std::string text)
{
    std::string str;
    str.append("\33[1;");
    str.append(color);
    str.append("m");
    str.append(text);
    str.append("\33[0m");
    return str.c_str();
}
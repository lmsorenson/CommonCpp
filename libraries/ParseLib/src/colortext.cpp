#include "colortext.hpp"
#include <string>

const char * SetColor(const char * color, const char * text)
{
    std::string str;
    str.append("\33[1;");
    str.append(color);
    str.append("m");
    str.append(text);
    str.append("\33[0m");
    return str.c_str();
}
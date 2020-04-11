#include "../colortext.hpp"
#include <string>

std::string sdg::utils::SetColor(std::string text, LogTextColor color)
{
    std::string str;
    str.append("\33[1;");
    str.append(std::to_string((int)color));
    str.append("m");
    str.append(text);
    str.append("\33[0m");
    return str.c_str();
}
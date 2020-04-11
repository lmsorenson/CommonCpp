#include <string>

// black        30         40
// red          31         41
// green        32         42
// yellow       33         43
// blue         34         44
// magenta      35         45
// cyan         36         46
// white        37         47

namespace sdg {
namespace utils {

enum class LogTextColor : int
{
    Black = 30,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White
};



std::string SetColor(std::string text, LogTextColor color);

}// namespace utils
}// namespace sdg
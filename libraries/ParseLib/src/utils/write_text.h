//loadText.h
#include <string>
#define WRITE_ERROR_STR ("Bad file path.")

namespace sdg {
namespace utils {

std::string writeText(std::string filepath, std::string contents);

}// namespace utils
}// namespace sdg
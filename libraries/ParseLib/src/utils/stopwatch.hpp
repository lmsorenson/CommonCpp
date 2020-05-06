#pragma once
#include <time.h>


namespace sdg {
namespace utils {

class Stopwatch
{
    clock_t t_; 
    double time_taken_;

public:
    void start();
    void stop();
    void reset();

    double read_seconds() const;

};

}// namespace utils
}// namespace sdg
#include "../stopwatch.hpp"


using ::sdg::utils::Stopwatch;



void Stopwatch::start()
{
    t_ = clock(); 
}

void Stopwatch::stop()
{
    t_ = clock() - t_;
    time_taken_ += ((double)t_);
}

void Stopwatch::reset()
{
    time_taken_ = 0;
}

double Stopwatch::read_seconds() const
{
    return time_taken_/CLOCKS_PER_SEC;
}
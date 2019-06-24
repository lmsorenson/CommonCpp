#include "AbstractFactory.hpp"
#include <iostream>


using namespace std;

void AbstractFactory::MakeRead()
{
    cout << "Make Read Strategy" << endl;
    return;
}

void AbstractFactory::MakeWrite()
{

    return;
}
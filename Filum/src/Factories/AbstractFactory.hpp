#pragma once
#include "../Reads/ReadStrategy.hpp"
#include "../Writes/WriteStrategy.hpp"



class AbstractFactory
{
public:
    ReadStrategy MakeRead();
    WriteStrategy MakeWrite();
};
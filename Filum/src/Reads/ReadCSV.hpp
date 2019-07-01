#include "ReadStrategy.hpp"



class ReadCSV : public ReadStrategy
{
    virtual std::vector<std::string> parse();
    virtual std::string select();
};
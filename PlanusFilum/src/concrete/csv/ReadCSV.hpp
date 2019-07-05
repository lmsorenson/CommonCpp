#include "../../abstract/Reads/ReadStrategy.hpp"



class ReadCSV : public ReadStrategy
{
    virtual std::vector<std::vector<std::string>> parse(const char * file_contents);
    virtual std::string select();
};
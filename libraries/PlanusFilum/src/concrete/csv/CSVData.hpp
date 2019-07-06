#include "../../abstract/DataStructures/AbstractDataStructure.hpp"



class CSVData : public AbstractDataStructure
{
public:
    CSVData();
    ~CSVData();

    virtual void assign();
};
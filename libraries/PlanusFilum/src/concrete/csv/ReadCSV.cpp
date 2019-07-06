#include "ReadCSV.hpp"
#include <iostream>
#include "../../../include/loadText.h"

using namespace std;


ReadCSV::ReadCSV()
{
    cout << "constructing csv read strategy. . . " << endl;
}

ReadCSV::~ReadCSV()
{
    cout << "destructing csv read strategy. . . " << endl;
}


vector<vector<string>> SeparateLines(const char * text);
vector<string> SeparateValues(const char * text);


vector<vector<string>> ReadCSV::parse(const char * file_contents)
{
    cout << "csv parse" << endl;

    vector<vector<string>> out = SeparateLines(file_contents);

    return out;
}


string ReadCSV::select()
{
    cout << "csv select" << endl;

    return "string";
}


//CHECK FOR POSIX
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <unistd.h>

vector<vector<string>> SeparateLines(const char * text)
{
    printf("\nPOSIX version: %i\n", _POSIX_VERSION);
    vector<vector<string>> ret_val;
    char * pch;
    char * end;
    printf ("Splitting string \"%s\" into tokens:\n", text);
    pch = strtok_r((char *)text,"\n", &end);
  
    while (pch != NULL)
    {
        printf ("%s\n",pch);
        ret_val.push_back(SeparateValues(pch));

        pch = strtok_r(NULL, "\n", &end);
    }

    return ret_val;
}


vector<string> SeparateValues(const char * text)
{
    printf("\nPOSIX version: %i\n", _POSIX_VERSION);

    vector<string> ret_val;
    char * pch;
    char * end;
    printf ("Splitting string \"%s\" into tokens:\n",text);
    pch = strtok_r((char *)text,", ", &end);

    while (pch != NULL)
    {
        printf ("%s\n",pch);
        ret_val.push_back(string(pch));
        pch = strtok_r(NULL, ", ", &end);
    }

    return ret_val;
}

#endif
//END CHECK FOR POSIX
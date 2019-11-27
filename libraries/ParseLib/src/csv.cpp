#include "../include/csv.h"

#include "../include/loadText.h"

using namespace std;

CSV SeparateLines(const char * text);
vector<string> SeparateValues(const char * text);

CSV file::loadCSV(const char * filepath)
{
    CSV ret_value;
    //  = SeparateLines(loadText(filepath));

    return ret_value;
}

//CHECK FOR POSIX
#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))
#include <unistd.h>

CSV SeparateLines(const char * text)
{
    printf("\nPOSIX version: %i\n", ((int)_POSIX_VERSION));
    CSV ret_val;
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
    printf("\nPOSIX version: %i\n", ((int)_POSIX_VERSION));

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
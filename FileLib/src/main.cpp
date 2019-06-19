#include <iostream>

using namespace std;

int main (int argc, char **argv)
{

	cout << "argc"  << argc << endl << "argv";

	for (int i=0; i<argc; ++i)
	{
		cout << argv[i] << " ";
	}

	cout << endl;
	
	return 0;
}

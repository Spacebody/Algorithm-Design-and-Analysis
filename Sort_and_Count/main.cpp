#include "MergeSort_and_Sort.hpp" //include the file

extern void Count_and_Print(string infile); //function definition outside this file

int main(int argc, char *argv[])
{
	if(argc == 1)
	{   //shall take a file name
		cerr<<"Usage:\n\tNo file name."<<endl; //print error message to screen
		exit(1);
	}
	else if(argc > 2)
	{    //only one file name allowed
		cerr<<"Usage:\n\tUnknown command."<<endl;
		exit(1);
	}
	Count_and_Print(argv[1]);		
	return 0;
}


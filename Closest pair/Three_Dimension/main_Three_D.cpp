#include "Closest_pair_Three_D.hpp"
#include <ctime>
void RandomSomePoint3(string infile);
int main(int argc, char *argv[])
{   
	if(argc == 0)
	{
		cerr<<"Need file."<<endl;
		exit(1);
	}
	else if(argc > 2)
	{
		cerr<<"Unknown command."<<endl;
		exit(1);
	}
	else
	{	
		RandomSomePoint3(argv[1]);
		Closest_pair_Three_D C(argv[1]);
		C.Closest_pair();
	}
	return 0;
}

void RandomSomePoint3(string infile)
{
	fstream iofile;
	iofile.open(infile, ios::out);
    srand(unsigned(time(0)));
    for(int i = 0; i != 10; ++i)
    {
    	iofile<<rand()%100<<","<<rand()%100<<","<<rand()%100<<endl; //put data to file
    }
    iofile.close();
}
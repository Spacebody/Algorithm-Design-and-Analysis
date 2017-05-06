#include "Closest_pair_One_D.hpp"

#include <ctime>
void RandomSomePoint1(string infile);

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
		RandomSomePoint1(argv[1]); //random some point between 0-100
		Closest_pair_One_D A(argv[1]);
		A.Closest_pair();
	}
	return 0;
}

void RandomSomePoint1(string infile)
{
	fstream iofile;
	iofile.open(infile, ios::out);
    srand(unsigned(time(0)));
    for(int i = 0; i != 10; ++i)
    {
    	iofile<<rand()%100<<endl;
    }
    iofile.close();
}
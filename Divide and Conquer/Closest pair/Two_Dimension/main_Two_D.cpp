#include "Closest_pair_Two_D.hpp"
#include <ctime>
void RandomSomePoint2(string infile);
int main(int argc, char *argv[])
{     //structure like main_One_D.cpp
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
		RandomSomePoint2(argv[1]);
		Closest_pair_Two_D B(argv[1]);
		B.Closest_pair();
	}
	return 0;
}

void RandomSomePoint2(string infile)
{
	fstream iofile;
	iofile.open(infile, ios::out);
    srand(unsigned(time(0)));
    for(int i = 0; i != 10; ++i)
    {
    	iofile<<rand()%100<<","<<rand()%100<<endl; //put random point to file
    }
    iofile.close();
}

#include "SegLeaSqu.hpp"

int main(int argc, char *argv[])
{
	if(argc == 0)
	{
		cerr<<"Need filename"<<endl;
		exit(1);
	}
	else if(argc > 3)
	{
		cerr<<"Unknown comman."<<endl;
		exit(1);
	}
	SegLeaSqu test(argv[1], atof(argv[2]));
	test.Print();
	return 0;
}
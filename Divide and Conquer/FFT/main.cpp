#include "SignalGenerator.hpp"
#include "FFT.hpp"

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cerr<<"Need file and sample numbers."<<endl;
		exit(1);
	}
	else if(argc > 3)
	{
		cerr<<"Unknown command."<<endl;
		exit(1);
	}
	else
	{	
		SignalGenerator Signal(argv[1], argv[2]); //generate signals
		FFT A(argv[1]); //fft process
		A.getResult(); //print out result
	}
	return 0;
}
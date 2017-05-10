#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <complex>
#include <string>
#include <fstream>
#define S(t) (double)(5+2.5*sin(2*PI*25*t)+3*sin(2*PI*100*t)) //signal function
#define delta 0.00390625//256Hz, sampling rate
#ifndef PI
#define PI 3.1415926535
#endif
#ifndef SignalGenerator
using namespace std;
class SignalGenerator
{
	private:
		int n;

		void Generate(string ifile)
		{
			ofstream output;
			output.open(ifile, ios::out);
			double t = 0;
			for(int i = 0; i < this->n;++i)
			{
				output<<setprecision(1)<<fixed<<S(t)<<endl; //export to file
				t += delta; 
			}
			output.close();
		} 
	public:
		SignalGenerator(string filename, string N)
		{
			this->n = atoi(N.c_str()); //get sample numbers 
			if( (n&n-1)!=0)
			{
				cerr<<"Need integer power of 2 data."<<endl;
				exit(1);
			}
			Generate(filename);
			cout<<"Singnal generated."<<endl;
		};
		~SignalGenerator(){};
};
#endif
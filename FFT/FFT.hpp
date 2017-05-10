#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <complex>
#include <string>
#include <fstream>
#define PI 3.1415926535
#ifndef FFT
using namespace std;
class FFT
{
	private:
		int n;
		vector<complex<double> > Sample; //store sample
		vector<complex<double> > Result; //store result
		void ReadSample(string ifile) 
		{	
			ifstream infile;
			infile.open(ifile, ios::in);
			if(infile.fail())
			{
				cerr<<"Failed to open file"<<endl;
			}
			else
			{
				string line;
				//read data from file
				while(!infile.eof())
				{	
					getline(infile, line);
					if(line == "\0")
					{
						continue;
					}
					double real, imag;
					//deal with the minus value
					if(line[0] == '-')
					{
						real = -atof(line.substr(1, '\n').c_str());	
					}
					else
					{
						real = atof(line.substr(0, '\n').c_str());
					}
					imag = 0;
					complex<double> comp(real, imag); //complex
					this->Sample.push_back(comp); //push into vector
				}
				infile.close();
				this->n = this->Sample.size();
				if( (n&(n-1)) != 0)
				{   //exam whether there are 2^integer numbers
					cerr<<"Need integer power of 2 data."<<endl;
					exit(1);
				}
			}
		}

		vector<complex<double> > fft(int n, vector<complex<double> > &a)
		{
			vector<complex<double> > y;
			if(n == 1)
			{
				return a;
			}
			//divide into two part
			vector<complex<double> > even_a, odd_a;
			for(int i = 0; i < n; ++i)
			{
				if(i%2 == 0)
				{
					even_a.push_back(a[i]);
				}
				else
				{
					odd_a.push_back(a[i]);
				}
			}
			vector<complex<double> > e = fft(n/2, even_a); 
			vector<complex<double> > d = fft(n/2, odd_a);
			
			//fft process
			for(int k = 0; k < n/2; ++k)
			{
				complex<double> w_k(cos(-2*PI*k/n),sin(-2*PI*k/n)); //wk
				y.push_back(e[k]+w_k*d[k]);
			}
			for(int k = 0;k < n/2; ++k)
			{
				complex<double> w_k(cos(-2*PI*k/n),sin(-2*PI*k/n));
				y.push_back(e[k]-w_k*d[k]);
			}
			return y; //return result
		}

	public:
		FFT(string filename)
		{
			ReadSample(filename);
		};
		~FFT(){cout<<"Process terminated."<<endl;}
		
		void getResult()
		{
			this->Result = fft(this->n, this->Sample); //get result by calling fft
			ofstream ofile;
			ofile.open("file/output.txt", ios::trunc);
			//export to file output.txt
			for(int i = 0;i < this->n;++i)
			{
				ofile<<i<<'\t'<<setprecision(1)<<fixed<<this->Result[i].real()<<" "<<this->Result[i].imag()<<"i"<<endl;
			}
			ofile.close();	
		}
};
#endif

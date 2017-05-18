#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <cfloat>
using namespace std;
typedef struct Point
{
	double x;
	double y;	
	int index;
}P;

typedef struct Segment
{
	int index_a;
	int index_b;	
}Line;

#ifndef SegLeaSqu
class SegLeaSqu
{
	private:
		int n;
		double c;
		vector<P> p;
		Line L;
		double e[100][100];
		vector<Line> Result;
		vector<double> M;
		
		//read data from file
		void ReadFile(string filename)
		{
			ifstream ifile;
			ifile.open(filename, ios::in);
			if(ifile.fail())
			{
				cerr<<"Failed to open file "<<filename<<endl;
				exit(1);
			}
			string line;
			int i = 0;
			while(!ifile.eof())
			{	
				getline(ifile, line);
				if(line == "\0")
				{
					continue;
				}
				char comma = line.find(',', 0);
				P tmp_p;
				tmp_p.x = atof(line.substr(0,comma).c_str());
				tmp_p.y = atof(line.substr(comma+1, '\n').c_str());
				tmp_p.index = i++;
				this->p.push_back(tmp_p);
			}
			this->n = (int)this->p.size();
		}
		
		//segment least squares
		vector<Line> SLS(int n, vector<P> &p, double c, double e[][100], vector<double> &M)
		{
			vector<Line> LL;
			vector<Line> Result;
			if(n == 1)
			{
				L.index_a = L.index_b = p[0].index;
				LL.push_back(L);
				return  LL; //L(0,0)
			}
			else if(n == 2)
			{
				L.index_a = p[0].index;
				L.index_b = p[1].index;
				LL.push_back(L);
				return LL; //L(0,1)
			}
			e = new double[100][100];
			for(int j = 0; j < n; ++j)
			{
				for(int i = 0;i < j;++i)
				{
					e[i][j] = (cal_eij(i, j, p)); //compute eij
				}
			}
			M.push_back(0); //M[0] = 0
			Line null;
			LL.push_back(null); //LL[0] = null
			for(int j = 1;j < n;++j)
			{
				int record_i = find_mini(e, c, j, M); //M[j] = ......
				if(record_i == j)
				{
					continue;
				}
				L.index_a = p[record_i].index;
				L.index_b = p[j].index;
				LL.push_back(L);
			}

			int tmp_a = LL[(int)LL.size()-1].index_a, tmp_b = LL[(int)LL.size()-1].index_b;
			Result.push_back(LL[(int)LL.size()-1]);
			for(int j = (int)LL.size()-2; j > 0; --j)
			{
				if(LL[j].index_b == tmp_a)
				{
					tmp_a = LL[j].index_a;
					tmp_b = LL[j].index_b;
					Result.push_back(LL[j]);
				}
			}

			return Result;
		}

		//calculate eij
		double cal_eij(int i, int j, vector<P> &p)
		{
			if(i == j)
			{
				return 0.0;
			}
			double a = 0.0, b = 0.0, eij = 0.0;
			double n = j-i+1;
			double s_x = 0.0, s_y = 0.0, s_xy = 0.0, s_x2 = 0.0;
			for(int k = i; k <= j;++k)
			{
				s_x += p[k].x;
				s_y += p[k].y;
				s_xy += p[k].x * p[k].y;
				s_x2 += p[k].x * p[k].x;
			}
			
			a = (n*s_xy-s_x*s_y)/(n*s_x2-s_x*s_x);
			b = (s_y - a*s_x)/n;

			for(int k = i; k<=j;++k)
			{
				eij += pow(p[k].y-a*p[k].x-b, 2);
			}
			if(eij < 1e-4)
			{
				eij = 0.0;
			}
			return eij;
		}

		int find_mini(double e[][100], double c, int j, vector<double> &M)
		{
			int record_i = 0; 
			double mini = DBL_MAX;
			for(int i = 0;i < j;++i)
			{
				if(e[i][j]+c+M[i] < mini)
				{
					mini = e[i][j]+c+M[i];
					record_i = i;
				}
			}
			M.push_back(mini); //M[j]
			return record_i;
		}

	public:
		SegLeaSqu(string filename, double c)
		{
			cout<<"Process is running..."<<endl;
			ReadFile(filename);
			this->c = c;
			this->Result = SLS(this->n, this->p, this->c, this->e, this->M);
		};
		~SegLeaSqu(){cout<<"Process terminated."<<endl;};
		//print out result
		
		void Print()
		{
			for(int i = 0; i < this->Result.size();++i )
			{
				cout<<"("<<this->Result[i].index_a<<","<<this->Result[i].index_b<<") "<<M[this->Result[i].index_b]<<endl;
			}	

			for(int i = 0; i < this->M.size();++i )
			{
				cout<<M[i]<<endl;
			}	
			
			// for(int i = 0; i < this->e.size();++i )
			// {
			// 	for(int j = 0;j<e[i].size();++j)
			// 	{
			// 		cout<<e[i][j]<<" ";
			// 	}
			// 	cout<<endl;
			// }	
		}
};
#endif
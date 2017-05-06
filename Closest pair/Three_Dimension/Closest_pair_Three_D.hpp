#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <float.h>
using namespace std;
typedef struct NodeRecord
{
	int x;
	int y;
	int z;
	int index;
	friend double operator - (const NodeRecord &a, const NodeRecord &b)
	{
		return fabs(sqrt(pow(a.x - b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2)));
	}  //distance
}Node;
bool compX(const Node &a, const Node &b)
{	
	return a.x < b.x;
}
bool compY(const Node &a, const Node &b)
{	
	return a.y < b.y;
}
bool compZ(const Node &a, const Node &b)
{	
	return a.z < b.z;
} //sorted by z
class Closest_pair_Three_D
{
	private:
		vector<Node> NodeArray;
		vector<Node> Result;
		vector<Node> Px;
		vector<Node> Py;
		vector<Node> Pz;
		void setNodeArray(string infile)
		{
			ifstream ifile;
			ifile.open(infile, ios::in);
			if(ifile.fail())
			{
				cerr<<"Error! Failed to open "<<infile<<endl;
				exit(1);
			}
			else
			{
				string line;
				while(!ifile.eof())
				{
					getline(ifile, line);
					if(line == "\0")
					{
						continue;
					}
					char comma = line.find(',', 0);
					char comma2 = line.find(',', comma+1); //second comma
					Node node;
					node.x = atoi(line.substr(0, comma).c_str());
					node.y = atoi(line.substr(comma+1, comma2-1).c_str());
					node.z = atoi(line.substr(comma2+1, '\n').c_str());
					node.index = -1;
					this->NodeArray.push_back(node);
				}
			}
			ifile.close();
		}

		vector<Node> Closest_pair_Rec(vector<Node> &Px, vector<Node> &Py,  vector<Node> &Pz)
		{
			vector<Node> result;
			if(Px.size()<=3)
			{
				if(Px.size() == 3)
				{
					if(Px[0] - Px[1] < Px[1] - Px[2])
					{
						result.push_back(Px[0]);
						result.push_back(Px[1]);
						return result;	
					}
					else
					{
						result.push_back(Px[1]);
						result.push_back(Px[2]);
						return result;		
					}
				}
				else if(Px.size() == 2)
				{
					result.push_back(Px[0]);
					result.push_back(Px[1]);
					return result;
				}
				else
				{
					cerr<<"Need at least two points"<<endl;
					exit(1);
				}
			}
			else
			{
				vector<Node> Qx, Rx, Qy, Ry, Qz, Rz, Q, R, P1, Pair_min;
				vector< vector<Node> > P2;
				int i = 0;
				for( ;i < Px.size()/2; ++i)
				{
					Qx.push_back(Px[i]);
					Qy.push_back(Px[i]);
					Qz.push_back(Px[i]);
				} //P1
				for(int j = i; j<Px.size(); ++j)
				{
					Rx.push_back(Px[j]);
					Ry.push_back(Px[j]);
					Rz.push_back(Px[j]);
				} //P2
				sort(Qy.begin(),Qy.end(),compY);
				sort(Ry.begin(),Ry.end(),compY);
				sort(Qz.begin(),Qz.end(),compZ);
				sort(Rz.begin(),Rz.end(),compZ);
				Q = Closest_pair_Rec(Qx, Qy, Qz);
				R = Closest_pair_Rec(Rx, Ry, Rz);
				double segma = min(Q[0]-Q[1], R[0]-R[1]);
				Node _x = Qx.back(); // x*
				vector<Node> tmpP2;
				for(int j = 0; j < Px.size();++j)
				{
					if(Px[j].x > _x.x)
					{
						tmpP2.push_back(Px[j]);
					}
				}
				P2.push_back(tmpP2);
				for(int j = 0; j< Px.size();++j)
				{

					if(Px[j].x <= _x.x)
					{
						int count = 0;
						for(int k = 0; k < P2[0].size();++k)
						{  //conut index
							if(Px[j].z > P2[0][k].z)
							{
								++count;
							}
						}
						Px[j].index = count;
						P1.push_back(Px[j]);
					}
				}
				sort(P1.begin(), P1.end(), compZ); //sort P1 by z
				sort(P2[0].begin(), P2[0].end(), compZ); //sort tmpP2 by z
				constructP1andP2(Px, Py, Pz, _x, segma, P1, P2);
				double dmin = DBL_MAX; //definition by "float.h"
				for(int j = 0; j < P1.size();++j)
				{
					Node _s, p;
					p = P1[j];
					_s = P2[0][P1[j].index];
					if(dmin > p - _s)
					{
						dmin = p - _s;
						Pair_min.push_back(p);
						Pair_min.push_back(_s);
					} 
				}
				dmin = DBL_MAX; 
				Pair_min.clear();
				if(dmin < segma)
				{
					return Pair_min;
				}
				else if(Q[0] - Q[1] < R[0] - R[1])
				{
					result.push_back(Q[0]);
					result.push_back(Q[1]);
					return result;
				}
				else
				{
					result.push_back(R[0]);
					result.push_back(R[1]);
					return result;
				}
			}
		} 

		void constructP1andP2(vector<Node> &Px, vector<Node> &Py, vector<Node> &Pz, \
			Node &_x, double segma, vector<Node> &P1, vector< vector<Node> > &P2)
		{
			Node y_min, y_max;
			vector<Node> tmpP2 = P2[0]; //temporarily store points in P2
			P2.clear();
			y_min = Py.front();
			y_max = Py.back();
			double d = 2*segma;
			int n = 0;
			if((y_max.y - y_min.y)/(2*d) - (int)((y_max.y - y_min.y)/(2*d)) > 0)
			{
				n = (int)((y_max.y - y_min.y)/(2*d))+1;
			}
			else
			{	
				n = (int)((y_max.y - y_min.y)/(2*d));
			}
			for(int i = 0; i < n; ++i)
			{
				vector<Node> segment;
				P2.push_back(segment);
			}
			for(int i = 0; i < n;++i)
			{
				for(int j = 0; j< tmpP2.size() && tmpP2[j] - y_min >= i*2*d && tmpP2[j] - y_min < (i+1)*2*d;++j)
				{
					P2[i].push_back(tmpP2[j]);
				}
				sort(P2[i].begin(), P2[i].end(), compY);
			}

			for(int i = 0; i < Pz.size();++i)
			{
				Node p = Pz[i];
				if(p.x - _x.x < segma && p.x <= _x.x)
				{
					int index = 0;
					for(int j = 0; j < P2.size();++j)
					{
						if(p.y - y_min.y >= j*d && p.y - y_min.y < (j+1)*d)
						{
							index = j;
						}  //to find which segment it should belong to
					}
					p.index = P2[index].size();
					P1.push_back(p);
				}
				if(Pz[i].x - _x.x < segma && Pz[i].x > _x.x)
				{
					int index = 0;
					for(int j = 0; j < P2.size();++j)
					{
						if(p.y - y_min.y >= j*d && p.y - y_min.y < (j+1)*d)
						{
							index = j;
						}  
					}
					P2[index].push_back(p);
				}
			}
		}

		
	public:
		Closest_pair_Three_D(string infile)
		{
			setNodeArray(infile);
		};
		~Closest_pair_Three_D()
		{
			cout<<"Process terminated."<<endl;
		};

		void Closest_pair()
		{
			this->Px = this->Py = this->Pz = this->NodeArray; 
			sort(this->Px.begin(), this->Px.end(), compX); //sorted by x
			sort(this->Py.begin(), this->Py.end(), compY); //sorted by y
			sort(this->Pz.begin(), this->Pz.end(), compZ); //sorted by z
			this->Result = Closest_pair_Rec(this->Px, this->Py, this->Pz);
			ofstream ofile;
			ofile.open("file/output3.txt", ios::trunc);
			for(int i = 0;i<this->Result.size();++i)
			{
				ofile<<this->Result[i].x<<", "<<this->Result[i].y<<", "<<this->Result[i].z<<endl;
			}
			ofile.close();
		}
};




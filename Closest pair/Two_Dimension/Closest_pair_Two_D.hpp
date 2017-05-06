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
	friend double operator - (const NodeRecord &a, const NodeRecord &b)
	{
		return fabs(sqrt(pow(a.x - b.x,2)+pow(a.y-b.y,2)));
	}  //distance
}Node;
bool compX(const Node &a, const Node &b)
{	
	return a.x < b.x; //sorted by x
}
bool compY(const Node &a, const Node &b)
{	
	return a.y < b.y; //sorted by y
}

class Closest_pair_Two_D
{
	private:
		vector<Node> NodeArray;
		vector<Node> Result;
		vector<Node> Px; //Nodearray sorted by x
		vector<Node> Py; //Nodearray sorted by y
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
				int i = 0;
				while(!ifile.eof())
				{
					getline(ifile, line);
					if(line == "\0")
					{
						continue;
					}
					char comma = line.find(',', 0); //find first comma
					Node node;
					node.x = atoi(line.substr(0, comma).c_str()); //get x 
					node.y = atoi(line.substr(comma+1, '\n').c_str()); //get y
					this->NodeArray.push_back(node);
				}
			}
			ifile.close();
		}

		vector<Node> Closest_pair_Rec(vector<Node> &Px, vector<Node> &Py)
		{
			vector<Node> result;
			if(Px.size()<=3)
			{
				if(Px.size() == 3)
				{
					if(Px[0] - Px[1] < Px[1]-Px[2])
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
				vector<Node> Qx, Rx, Qy, Ry, Q, R, Sy, Pair_min, Pair;
				int i = 0;
				for( ;i < Px.size()/2; ++i)
				{
					Qx.push_back(Px[i]);
					Qy.push_back(Px[i]);
				} //P1
				for(int j = i; j<Px.size(); ++j)
				{
					Rx.push_back(Px[j]);
					Ry.push_back(Px[j]);
				} //P2
				sort(Qy.begin(),Qy.end(),compY); //sorted by y
				sort(Ry.begin(),Ry.end(),compY);
				Q = Closest_pair_Rec(Qx, Qy);
				R = Closest_pair_Rec(Ry, Ry);
				double segma = min(Q[0]-Q[1], R[0]-R[1]);
				Node _x = Qx.back();
				for(int j = 0; j < Py.size(); ++j)
				{
					if(Py[j] - _x < segma)
					{
						Sy.push_back(Py[j]);
					}
				}
				double dmin = DBL_MAX;
				for(int j = 0; j < Sy.size() && Sy[j].x <= _x.x;++j)
				{
					Node s, _s;
					s = Sy[j];
					for(int k = 0; k< Sy.size() && Sy[k].x > _x.x && fabs(Sy[k].y - s.y) <= segma; ++k)
					{
						_s = Sy[k];
						if(dmin < s - _s)
						{	
							dmin = s - _s;
							Pair_min.push_back(s);
							Pair_min.push_back(_s);
						}
					}	
				}
				if(dmin < segma) 
				{
					return Pair_min;
				}
				else if(Q[0]-Q[1] < R[0]-R[1])
				{
					
					Pair.push_back(Q[0]);
					Pair.push_back(Q[1]);
					return Pair;
				}
				else
				{
					Pair.push_back(R[0]);
					Pair.push_back(R[1]);
					return Pair;
				}	
			}
		} 

		
	public:
		Closest_pair_Two_D(string infile)
		{
			setNodeArray(infile);
		};
		~Closest_pair_Two_D()
		{
			cout<<"Process terminated."<<endl;
		};

		void Closest_pair()
		{
			this->Px = this->NodeArray; 
			this->Py = this->NodeArray; 
			sort(this->Px.begin(), this->Px.end(), compX); //sorted by x
			sort(this->Py.begin(), this->Py.end(), compY); //sorted by y
			this->Result = Closest_pair_Rec(this->Px, this->Py);
			ofstream ofile;
			ofile.open("../file/output2.txt", ios::trunc);
			for(int i = 0;i<this->Result.size();++i)
			{
				ofile<<this->Result[i].x<<", "<<this->Result[i].y<<endl; //print out to file
			}
			ofile.close();
		}
};




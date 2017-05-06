#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;
typedef struct NodeRecord
{
	int x;
	friend bool operator < (const NodeRecord &a, const NodeRecord &b)
	{
		return a.x < b.x;
	}
	friend int operator - (const NodeRecord &a, const NodeRecord &b)
	{
		return abs(a.x - b.x);
	} //return distance 
}Node;

bool compX(const Node &a, const Node &b)
{	
	return a.x < b.x;
}

class Closest_pair_One_D
{
	private:
		vector<Node> NodeArray;
		vector<Node> Result; //result we will return 
		vector<Node> Px; //after sorting by x
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
					Node node;
					node.x = atoi(line.c_str()); //get data from line
					this->NodeArray.push_back(node);
				}
			}
			ifile.close();
		}

		vector<Node> Closest_pair_Rec(vector<Node> &Array)
		{
			vector<Node> result;
			if(Array.size()<=3)
			{ //less than three points
				if(Array.size() == 3)
				{
					if(Array[0] - Array[1] < Array[1]-Array[2])
					{
						result.push_back(Array[0]);
						result.push_back(Array[1]);
						return result;	
					}
					else
					{
						result.push_back(Array[1]);
						result.push_back(Array[2]);
						return result;		
					}
				}
				else if(Array.size() == 2)
				{
					result.push_back(Array[0]);
					result.push_back(Array[1]);
					return result;
				}
				else
				{	//print out error message
					cerr<<"Need at least two points"<<endl;
					exit(1);
				}
			}
			else
			{
				vector<Node> Qx, Rx, Q, R;
				int i = 0;
				for( ;i < Array.size()/2; ++i)
				{
					Qx.push_back(Array[i]);
				} //P1
				for(int j = i; j<Array.size(); ++j)
				{
					Rx.push_back(Array[j]);
				}  //P2
				Q = Closest_pair_Rec(Qx); //recursion
				R = Closest_pair_Rec(Rx);
				int segma = min(Q[0]-Q[1], R[0]-R[1]);
				Node _x = Qx.back(); //the largest point in P1
				Node _s = Rx.front(); //the first point in P2
				if( _x -_s < segma)
				{
					result.push_back(_x);
					result.push_back(_s);
					return result;
				}
				else if(Q[0]-Q[1] < R[0]-R[1])
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

		
	public:
		Closest_pair_One_D(string infile)
		{
			setNodeArray(infile); //initialize the nodes
		};
		~Closest_pair_One_D()
		{
			cout<<"Process terminated."<<endl; //prompt to terminate
		};

		void Closest_pair()
		{
			this->Px = this->NodeArray;
			sort(this->Px.begin(), this->Px.end(), compX);//sort in increasing order
			this->Result = Closest_pair_Rec(Px);
			ofstream ofile;
			ofile.open("../file/output1.txt", ios::trunc); //create file  file
			for(int i = 0;i<this->Result.size();++i)
			{
				ofile<<this->Result[i].x<<endl;
			}
			ofile.close();
		}
};




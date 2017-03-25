#include "Headers.h"
using namespace std;

class Node
{
	private:
		string Name;
		int No;
		double x;
		double y;
		double dist;
	public:
		Node(){}; //constructor 
		~Node(){}; //deconstructor
		//set the name
		void setName(string Name)
		{
			this->Name = Name;
		}
		//get the name
		string getName() const
		{
			return this->Name;
		}
		//set the number of node 
		void setNo(int No)
		{
			this->No = No;
		}
		//get NO
		int getNo() const
		{
			return this->No;
		}
		//set offset
		void setOffset(double offset[][2], int i)
		{
			this->x = offset[i][0];
			this->y = offset[i][1];
		}	
		//get x offset
		double getX()
		{
			return this->x;
		}
		//get y offset
		double getY()
		{
			return this->y;
		}

		//overload operator <, node will be order by "No"
		bool operator < (const Node &node) const
		{
			return this->No < node.No;
		} 
 		//overload operator ==, to be use in find()
		bool operator == (const Node &node) const
		{
      		return this->No == node.No;
		}
		//set distance
		void setDist(double dist)
		{
			this->dist = dist;
		}
		//get distance
		double getDist() const
		{
			return this->dist;
		}
};
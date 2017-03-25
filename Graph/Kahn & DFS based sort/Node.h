#ifndef Node_h
#define Node_h
class Node
{
	private:
		int NO; //number of node 
		int indegree; //indegree of node 
		int outdegree; //outdegree of node 
		bool visit; //if visited?
		int stateNum; //visit state {-1, 0, 1}
	public:
		Node();
		~Node();

		void setNO(int no);
		int getNO();
		void setIndegree(int indegree);
		int getIndegree() const;
		void setOutdegree(int outdegree);
		int getOutdegree() const;
		//alter indegree
		void altIndegree(int x);
		//alter outdegree
		void altOutdegree(int x);
		//set visit
		void setState(bool state);
		//get visit
		bool getState();
		void setstateNum(int num);
		int getstateNum();
		//overload operator <, node will be order by "No"
		bool operator < (const Node &node) const;
 		//overload operator ==, to be use in find()
		bool operator == (const Node &node) const;
};
#endif

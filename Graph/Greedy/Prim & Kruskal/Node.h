#ifndef Node_h
#define Node_h
class Node
{
	private:
		int NO; //number of node
		bool visit; //if visited?
		int Color; //visit state {white, grey, black}
	public:
		Node();
		~Node();

		void setNO(int no);
		int getNO() const;
		
		void setState(bool state); //set visit
		bool getState() const; //get visit

		void setColor(int num); //set stateNum
		int getColor() const; //get stateNum

		//overload operator <, node will be order by "No"
		bool operator < (const Node &node) const;
 		//overload operator ==, to be use in find()
		bool operator == (const Node &node) const;
};
#endif

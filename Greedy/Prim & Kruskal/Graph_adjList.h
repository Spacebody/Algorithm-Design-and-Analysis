#ifndef _Headers_h
#include "Headers.h"
#endif

#ifndef Node_h_
#include "Node.h"
#endif

#ifndef Graph_h
#define Graph_h

class Graph_adjList
{
	private:
		vector<Node> NodeArray; //node in array
		vector<map<Node, int> > MapArray;  //store map in array
		map<Node, map<Node, int> > Graph; //map of node and edge

	public:
		Graph_adjList();
		~Graph_adjList();
		
		void InitGraph(int NO[], int matrix[][N]); //initialize graph
		vector<Node> getNodeArray();  //get array which store nodes
		vector<map<Node, int> > getMapArray(); //get array which store maps
		map<Node, map<Node, int> > getGraph(); //get generated graph 
};
#endif
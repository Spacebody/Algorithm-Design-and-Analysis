#ifndef Headers_h_
#include "Headers.h"
#endif
#ifndef Node_h_
#include "Node.h"
#endif

#ifndef Graph_adjList_h
#define Graph_adjList_h

typedef list<Node> AdjList; //list

class Graph_adjList
{
	private:
		vector<Node> NodeArray; //node in array
		vector<list<Node> > ListArray; //store list in array
		map<Node, list<Node> > Graph; //map of node and edge


	public:
		Graph_adjList();
		~Graph_adjList();
		
		void InitGraph(int NO[], int matrix[][N]);
		vector<Node> getNodeArray();
		vector<list<Node> > getListArray();
		map<Node, list<Node> > getGraph();
};
#endif
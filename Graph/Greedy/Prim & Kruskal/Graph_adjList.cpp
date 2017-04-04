#include "Graph_adjList.h"

Graph_adjList::Graph_adjList()
	{
		cout<<"Graph in adjacent list created."<<endl;
	};
	Graph_adjList::~Graph_adjList()
	{
		cout<<"Graph in adjacent list destoryed."<<endl;
	};

	void Graph_adjList::InitGraph(int NO[], int matrix[][N])
	{  
		for(int i = 0; i < N; ++i)
		{
			this->NodeArray.push_back(Node()); //push into array
			this->NodeArray[i].setNO(NO[i]); //set the NO
			this->NodeArray[i].setState(false);
			this->NodeArray[i].setColor(white);
		} //vector set

		for(int i = 0; i < N; ++i)
		{
			map<Node, int> map; 
			for(int j = 0; j < N; ++j)
			{
				if(matrix[i][j] > 0)
				{
					map.insert(pair<Node, int>(NodeArray[j], matrix[i][j]));
         		} 
			}
			this->MapArray.push_back(map);
		} //linked edge set

		for(int i = 1; i <= N; ++i)
		{
			this->Graph.insert(pair<Node, map<Node,int> >(NodeArray[N-i], MapArray[N-i]));//generate graph
		} //graph by adjacency list
	}

	vector<Node> Graph_adjList::getNodeArray() 
	{
		return this->NodeArray;
	}

	vector<map<Node, int> > Graph_adjList::getMapArray() 
	{
		return this->MapArray;
	}

	map<Node, map<Node, int> > Graph_adjList::getGraph() 
	{
		return this->Graph;
	}
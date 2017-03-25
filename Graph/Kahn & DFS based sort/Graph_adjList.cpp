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
		int indegree = 0, outdegree = 0;
		
		for(int i = 0; i < N; ++i)
		{
			NodeArray.push_back(Node()); //push into array
			NodeArray[i].setNO(NO[i]); //set the NO
			NodeArray[i].setIndegree(0);
			NodeArray[i].setOutdegree(0);
			NodeArray[i].setState(false);
			NodeArray[i].setstateNum(-1);
		} //vector set

		for(int i = 0; i < N; ++i)
		{
			AdjList List; 
			for(int j = 0; j < N; ++j)
			{
				if(matrix[i][j] == 1)
				{
					NodeArray[i].setOutdegree(NodeArray[i].getOutdegree()+1);
					NodeArray[j].setIndegree(NodeArray[j].getIndegree()+1);
					List.push_back(NodeArray[j]);
         		}
			}
			ListArray.push_back(List);
		} //linked edge set
		for(int i = 1; i <= N; ++i)
		{
			this->Graph.insert(pair<Node, list<Node> >(NodeArray[N-i], ListArray[N-i]));//generate graph
		} //graph by adjacency list
	}

	vector<Node> Graph_adjList::getNodeArray() 
	{
		return this->NodeArray;
	}

	vector<list<Node> > Graph_adjList::getListArray() 
	{
		return this->ListArray;
	}

	map<Node, list<Node> > Graph_adjList::getGraph() 
	{
		return this->Graph;
	}
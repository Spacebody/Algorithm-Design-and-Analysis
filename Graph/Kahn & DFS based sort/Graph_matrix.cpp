#include "Graph_matrix.h"

	Graph_matrix::Graph_matrix()
	{
		cout<<"Graph in adjacent matrix created"<<endl;
	};
	Graph_matrix::~Graph_matrix()
	{
		cout<<"Graph in adjacent matrix destoryed"<<endl;
	};

	void Graph_matrix::setNodeArray(int num[])
	{
		for(int i = 0;i < N;++i)
		{	//initilize the members
			this->NodeArray.push_back(Node());
			this->NodeArray[i].setNO(num[i]);
			this->NodeArray[i].setIndegree(0);
			this->NodeArray[i].setOutdegree(0);
			this->NodeArray[i].setState(false);
		}
	}

	void Graph_matrix::InitGraph(int matrix[][N], int num[], Node Matrix[][N])
	{
		setNodeArray(num);
		for(int i = 0;i<N;++i)
		{
			for(int j = i;j<N;++j)
			{
				if(matrix[i][j] == 1)
				{	//set the indegree and outdegree
					this->NodeArray[i].setOutdegree(this->NodeArray[i].getOutdegree()+1);
					this->NodeArray[j].setIndegree(this->NodeArray[j].getIndegree()+1);
				}
			}
		}
		for(int i = 0;i<N;++i)
		{
			this->adjMatrix[i][i] = this->NodeArray[i];
			Matrix[i][i] = this->NodeArray[i];
			for(int j = i; j<N;++j)
			{
				if(matrix[i][j] == 1)
				{
					this->adjMatrix[i][j] = this->NodeArray[j];
					Matrix[i][j] = this->NodeArray[j];
				}
			}
		}
	}


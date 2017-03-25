#include "Node.cpp"
#include "Graph_adjList.cpp"
#include "Graph_matrix.cpp"

void Kahn(map<Node, list<Node> > &Graph1, vector<Node> &PrintList1); //Kahn algorithm
void DFS(map<Node, list<Node> > &Graph1, vector<Node> &PrintList2); //Topological sort based on DFS
void Visit(Node &n, map<Node, list<Node> > &Graph1, vector<Node> &PrintList2); //visit node
void mDFS(map<Node, list<Node> > &Graph1); //exam whether graph has circle
void mVisit(Node &n, map<Node, list<Node> > &Graph1);//for mDFS use

void Kahn2(Node Matrix[][N], vector<Node> &PrintList3, int matrix[][N]); //Kahn algorithm
void DFS2(Node Matrix[][N], int matrix[][N], vector<Node> &PrintList4); //Topological sort based on DFS
void Visit2(Node &n, Node Matrix[N][N], int matrix[N][N],vector<Node> &PrintList4); //for DFS2 use

int main(void)
{
	int num[] = {1,2,3,4,5,6,7,8};
	int matrix[][N]={0,1,1,0,0,0,0,0,
					 0,0,1,1,1,0,0,0,
				     0,0,0,0,1,0,1,1,
		         	 0,0,0,0,1,0,0,0,
					 0,0,0,0,0,1,0,0,
					 0,0,0,0,0,0,0,0,
					 0,0,0,0,0,0,0,1,
					 0,0,0,0,0,0,0,0};

	Graph_adjList Graph; //create a object
	Graph.InitGraph(num, matrix); //generate the graph
	map<Node, list<Node> > Graph1 = Graph.getGraph(); //get the graph
	
	vector<Node> PrintList1, PrintList2; //list to print
    //adjacent list
	Kahn(Graph1, PrintList1);
	cout<<"Kahn: ";
	for(int i = 0;i<N;++i)
	{
		cout<<PrintList1[i].getNO()<<"  ";
	}
	cout<<endl;

	DFS(Graph1, PrintList2);
	cout<<"DFS: ";
	for(int i = 0;i<N;++i)
	{
		cout<<PrintList2[i].getNO()<<"  ";
	}
	cout<<endl;
	Graph.~Graph_adjList();
	cout<<endl;


	vector<Node> PrintList3, PrintList4;

	Node Matrix[N][N] = {Node()};
	Graph_matrix Graph2;
	Graph2.InitGraph(matrix, num, Matrix);
	//adjacent matrix
	Kahn2(Matrix, PrintList3, matrix);
	cout<<"Kahn: ";
	for(int i = 0;i<N;++i)
	{
		cout<<PrintList3[i].getNO()<<"  ";
	}
	cout<<endl;
	DFS2(Matrix, matrix, PrintList4);
	cout<<"DFS: ";
	for(int i = 0;i<N;++i)
	{
		cout<<PrintList4[i].getNO()<<"  ";
	}
	cout<<endl;
	Graph2.~Graph_matrix();
	cout<<endl;

	Graph_adjList Graph3;
	Graph3.InitGraph(num, matrix);
	map<Node, list<Node> > GraphO = Graph3.getGraph();
	//modified DFS to exam the circle in graph
	mDFS(GraphO);
	cout<<endl;
	return 0;
}

//Kahn
void Kahn(map<Node, list<Node> > &Graph1, vector<Node> &PrintList1)
{
	queue<Node> tmpList;
	map<Node, list<Node> >::iterator iter;
	for(iter = Graph1.begin(); iter!=Graph1.end();++iter)
	{
		if(iter->first.getIndegree() == 0)
		{
			tmpList.push(iter->first); //if indegree is 0, push into queue
		}
	}
	while(!tmpList.empty())
	{ //loop while queue is not empty
		PrintList1.push_back(tmpList.front());
		Node &tmp = tmpList.front();
		tmpList.pop(); //pop out the first element
		list<Node>::iterator iter2;
		iter = Graph1.find(tmp);
		for(iter2 = iter->second.begin();iter2!=iter->second.end();++iter2)
		{   //for every node which has egde with node tmp
			(*iter2).setIndegree((*iter2).getIndegree()-1); //delete the edge
			if((*iter2).getIndegree() == 0)
			{
				tmpList.push(*iter2); //if indegree is 0, push into queue
			}
		}
	}
}

//DFS
void DFS(map<Node, list<Node> > &Graph1, vector<Node> &PrintList2)
{
	queue<Node> tmpList;
	map<Node, list<Node> >::iterator iter;
	for(iter = Graph1.begin(); iter!=Graph1.end();++iter)
	{
		if(iter->first.getIndegree() == 0)
		{
			tmpList.push(iter->first);
		}
	}
	while(!tmpList.empty())
	{
		Node &n = tmpList.front();
		Visit(n, Graph1, PrintList2);
		tmpList.pop();
	}

}	

void Visit(Node &n, map<Node, list<Node> > &Graph1, vector<Node> &PrintList2)
{
	map<Node, list<Node> >::iterator iter;
	if(n.getState() == false)
	{	//visit it if not been visited
		n.setState(true);
		list<Node>::iterator iter2;
		iter = Graph1.find(n);
		for(iter2 = iter->second.begin();iter2!=iter->second.end();++iter2)
		{	//visit every node which has egde with node n
			Visit(*iter2, Graph1, PrintList2);
		}
		PrintList2.push_back(n);
	}
}

//modified DFS to exam circle in a graph
void mDFS(map<Node, list<Node> > &Graph1)
{
	queue<Node> tmpList;
	map<Node, list<Node> >::iterator iter;
	for(iter = Graph1.begin();iter!=Graph1.end();++iter)
	{
		//cout<<iter->first.getIndegree()<<" "<<iter->first.getOutdegree()<<endl;
		if(iter->first.getIndegree() == 0)
		{
			tmpList.push(iter->first);
		}
	}
	while(!tmpList.empty())
	{
		Node &n = tmpList.front();
		mVisit(n, Graph1);
		tmpList.pop();
	}

}	

void mVisit(Node &n, map<Node, list<Node> > &Graph1)
{
	map<Node, list<Node> >::iterator iter;
	if(n.getstateNum() == -1)
	{
		n.setstateNum(0);
		list<Node>::iterator iter2;
		iter = Graph1.find(n);
		for(iter2 = iter->second.begin();iter2!=iter->second.end();++iter2)
		{
			mVisit(*iter2, Graph1);
		}
		n.setstateNum(1);
	}
	else if(n.getstateNum() == 0)
	{
		cout<<"This graph has circle."<<endl;
		exit(0);
	}
	else
	{
		cout<<"This graph has no circle"<<endl;
		exit(0);
	}
}

void Kahn2(Node Matrix[][N], vector<Node> &PrintList3, int matrix[][N])
{
	queue<Node> tmpList;
	for(int i = 0; i<N; ++i)
	{
		if(Matrix[i][i].getIndegree() == 0)
		{
			tmpList.push(Matrix[i][i]);
		}
	}
	while(!tmpList.empty())
	{
		PrintList3.push_back(tmpList.front());
		Node &tmp = tmpList.front();
		tmpList.pop();
		for(int i = tmp.getNO()-1, j = i+1; j<N; ++j)
		{
			if(matrix[i][j]== 1 && Matrix[i][j].getIndegree() > 0)
			{	//delete edge
				Matrix[j][j].setIndegree(Matrix[j][j].getIndegree()-1);
				if(Matrix[j][j].getIndegree() == 0)
				{
					tmpList.push(Matrix[j][j]);
				}
			}
		}
		
	}
}

void DFS2(Node Matrix[][N], int matrix[][N], vector<Node> &PrintList4)
{
	queue<Node> tmpList;
	for(int i = 0; i<N; ++i)
	{
		if(Matrix[i][i].getIndegree() == 0)
		{
			tmpList.push(Matrix[i][i]);
		}
	}
	while(!tmpList.empty())
	{
		Node &tmp = tmpList.front();
		Visit2(tmp, Matrix,matrix,PrintList4);
		tmpList.pop();
	}
}

void Visit2(Node &n, Node Matrix[][N], int matrix[][N],vector<Node> &PrintList4)
{
	if(n.getState() == false)
	{
		n.setState(true);
		for(int i = n.getNO()-1,j=i+1;j<N;++j)
		{
			if(matrix[i][j]== 1)
			{
				Visit2(Matrix[i][j], Matrix, matrix, PrintList4);
			}
		}
		PrintList4.push_back(n);
	}
}

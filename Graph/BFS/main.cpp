#ifndef Headers_h
#include "Headers.h"
#endif 
#include "Node.cpp"

//definition of node and list
typedef list<Node> NodeList; //linked nodes of every node 
typedef vector<NodeList> ListArray; //store list in vector
typedef vector<Node> NodeArray; //store node
typedef map<Node, NodeList> UnWGraph; //unweighted graph
typedef map<Node, double> WeightList; //weight list
typedef vector<WeightList> Weight; //weight list store in array 
typedef map<Node, WeightList> WGraph; //weighted graph
typedef queue<Node> NodeQueue;

//adjacent list
void InitUnWGraph(string NodeName[], int UnWmatrix[][N], \
	UnWGraph &Graph1, NodeArray &List); //initialize the unweighted graph
void InitWGraph(string NodeName[], int UnWmatrix[][N], double Offset[][2], \
	WGraph &Graph2, NodeArray &List); //weighted graph
void BFSofUnWGraph(int node, UnWGraph &Graph1, NodeArray &List);
void BFSofWGraph(int node, WGraph &Graph2, NodeArray &List);

//adjacent matrix (for unweighted graph, just modified value in the matrix to be 1)
void InitWGraph2(string NodeName[], int UnWmatrix[][N], \
	double Offset[][2], NodeArray &List, Node Graph3[][N]); //weighted graph
void BFSofWGraph2(int node, Node Graph3[][N], NodeArray &List);

//main function
int main(void)
{	//graph message for generate graph by function
	string NodeName[N] = {"1","2","3","4","5","6","7","8"};
	int UnWmatrix[][N] = {0,1,1,0,0,0,0,0,
					      1,0,1,1,1,0,0,0,
					      1,1,0,0,1,0,1,1,
					      0,1,0,0,1,0,0,0,
					      0,1,1,1,0,1,0,0,
					      0,0,0,0,1,0,0,0,
					      0,0,1,0,0,0,0,1,
					      0,0,1,0,0,0,1,0}; //1 means two nodes linked by an edge 
	double Offset[N][2] = {2,6,
	                       1,4,
	                 	   3,4,
	                       0,2,
	                 	   2,2,
	                 	   2,0,
	                 	   4,6,
	                 	   4,2};
	                 	                    	   
	NodeArray List; //node
	UnWGraph Graph1; //unweighted graphs
	WGraph Graph2; //weighted graph
	Node Graph3[N][N] = {Node()};
	InitUnWGraph(NodeName, UnWmatrix, Graph1, List);
	InitWGraph(NodeName, UnWmatrix, Offset, Graph2, List);
	InitWGraph2(NodeName, UnWmatrix, Offset, List, Graph3);
/**
 *test code to exam the graph
 *
	UnWGraph::iterator iter1;
	NodeList::iterator iter2;
	for(iter1 = Graph1.begin();iter1 != Graph1.end();++iter1)
	{
		cout<<iter1->first.getName()<<" ";
		for(iter2 = iter1->second.begin();iter2 != iter1->second.end();++iter2)
		{
			cout<<(*iter2).getName();
		}
		cout<<endl;
	}
	WGraph::iterator iter1;
	WeightList::iterator iter2;
	for(iter1= Graph2.begin();iter1 != Graph2.end(); ++iter1)
	{
		cout<<iter1->first.getName()<<"    ";
		for(iter2 = iter1->second.begin();iter2!=iter1->second.end();++iter2)
		{
			cout<<iter2->first.getName()<<" dist:"<<fixed<<setprecision(3)<<iter2->second<<"   ";
		}
		cout<<endl;
	}

	for(int i = 0;i<N;++i)
	{
		for(int j = 0;j<N;++j)
		{
			cout<<fixed<<setprecision(2)<<Graph3[i][j].getDist()<<"   ";
		}
		cout<<endl;
	}
*/
	int node;
	cout<<"Please enter node: "<<endl;
	cin>>node;
	cout<<"For unweighted graph:"<<endl;
	BFSofUnWGraph(node, Graph1, List);
	cout<<"For weighted graph:"<<endl;
	BFSofWGraph(node, Graph2, List);	
	cout<<"Use matrix:"<<endl;
	BFSofWGraph2(node, Graph3, List);
	return 0;
}

//Adjacent list
//unweighted graph
void InitUnWGraph(string NodeName[], int UnWmatrix[][N], UnWGraph &Graph1, NodeArray &List)
{  
	ListArray EdgeList; //edge
	for(int i = 0; i < N; ++i)
	{
		List.push_back(Node()); //push into vector
		List[i].setName(NodeName[i]); //set the name
		List[i].setNo(i+1); //set number
		List[i].setDist(0); //set distance
	} //vector set
	for(int i = 0; i < N; ++i)
	{
		EdgeList.push_back(NodeList()); 
		NodeList &tmp = EdgeList.back();
		for(int j = 0; j < N; ++j)
		{
			if(UnWmatrix[i][j] == 1)
			{
				tmp.push_back(List[j]);
            }
		}
	} //linked edge set
	for(int i = 1; i <= N; ++i)
	{
		Graph1.insert(pair<Node, NodeList>(List[N-i], EdgeList[N-i]));//generate graph
	} //graph by adjacency list
}

//weighted graph
void InitWGraph(string NodeName[], int UnWmatrix[][N], \
	double Offset[][2], WGraph &Graph2, NodeArray &List)
{
	Weight WeightArray;	
	for(int i = 0; i < N; ++i)
	{
		List.push_back(Node()); 
		List[i].setName(NodeName[i]); 
		List[i].setNo(i+1); 
		List[i].setOffset(Offset, i); //set the offset 
		List[i].setDist(0); 
	} //vector set
	for(int i = 0; i<N;++i)
	{
		WeightArray.push_back(WeightList());
		WeightArray[i].insert(pair<Node, double>(List[i],0));
		for(int j = N-1; j >= 0 ; --j)
		{
			if(UnWmatrix[i][j] == 1)
			{
				double dist = sqrt(pow(List[i].getX()-List[j].getX(), 2.0)\
				+pow(List[i].getY()-List[j].getY(), 2.0));//distance
				WeightArray[i].insert(pair<Node, double>(List[j], dist));
			}
		} //edge and distance
	}
	for(int i = 1;i<=N;++i)
	{
		Graph2.insert(pair<Node, WeightList>(List[N-i], WeightArray[N-i])); //generate graph
	}
}

//BFS for unweighted graph
void BFSofUnWGraph(int node, UnWGraph &Graph1, NodeArray &List)
{
	NodeQueue Q; //search queue
	NodeArray SearchList; //record the node ever searched
	UnWGraph::iterator iter1;
	NodeList::iterator iter2;
	Q.push(List[node-1]); //push start into queue 
	SearchList.push_back(List[node-1]); 
	while(!Q.empty())
	{  //loop while queue is not empty
		Node &tmp = Q.front();	
		cout<<node<<" -> "<<tmp.getName()+": "<<tmp.getDist()<<endl; //print out distance
		iter1 = Graph1.find(tmp); //map the node 
		for(iter2 = iter1->second.begin();iter2!=iter1->second.end();++iter2)
		{
			NodeArray::iterator Find = find(SearchList.begin(), SearchList.end(), *iter2); //try find in vector
			if(Find == SearchList.end())
			{ //if not found, push into queue 
				(*iter2).setDist(tmp.getDist()+1);
				Q.push(*iter2);
				SearchList.push_back(*iter2); //record the node
			}
		}
		Q.pop();
	}
}

//BFS for weighted graph
void BFSofWGraph(int node, WGraph &Graph2, NodeArray &List)
{
	NodeQueue Q;
	NodeArray SearchList;
	WGraph::iterator iter1;
	WeightList::iterator iter2;
	double dist = 0;
	Q.push(List[node-1]);
	SearchList.push_back(List[node-1]);
	while(!Q.empty())
	{
		Node &tmp = Q.front();
		iter1 = Graph2.find(tmp);
		cout<<node<<" -> "+tmp.getName()+": "<<fixed<<setprecision(2)<<tmp.getDist()<<endl; //print the result
		for(iter2 = iter1->second.begin();iter2!=iter1->second.end();++iter2)
		{
			dist = tmp.getDist(); 
			NodeArray::iterator Find = find(SearchList.begin(), SearchList.end(), iter2->first);//try find in vector
			if(Find == SearchList.end())
			{  //if not found, push into queue 
				Node tmp2 = iter2->first; //calculate distance 
				tmp2.setDist(iter2->second+dist); //set distance
				Q.push(tmp2);
				SearchList.push_back(tmp2); 
			}
		}
		Q.pop();
	}
}

//adjacent matrix
void InitWGraph2(string NodeName[], int UnWmatrix[][N], double Offset[][2], NodeArray &List, Node Graph3[][N])
{
	ListArray EdgeList; //edge
	for(int i = 0; i < N; ++i)
	{
		List.push_back(Node()); //push into vector
		List[i].setName(NodeName[i]); //set the name
		List[i].setNo(i+1); //set number
		List[i].setOffset(Offset, i); //set the offset 
		List[i].setDist(0); //set distance
	} //vector set
	for(int i = 0;i<N;++i)
	{
		for(int j = 0;j<N;++j)
		{
			Graph3[i][j].setName(NodeName[j]); //set as initial value
			Graph3[i][j].setDist(0); //distance is 0 at first
			Graph3[i][j].setNo(i+1);
			if(UnWmatrix[i][j] == 1)
			{
				Graph3[i][j] = List[j]; //set the node if having edge
				double dist = sqrt(pow(List[i].getX()-List[j].getX(), 2.0)\
				+pow(List[i].getY()-List[j].getY(), 2.0));//distance
				Graph3[i][j].setDist(dist); //set distance
			}
		}
	}
}

void BFSofWGraph2(int node, Node Graph3[][N], NodeArray &List)
{
	NodeQueue Q;
	NodeArray SearchList;
	Q.push(Graph3[node-1][node-1]); //push the start node into queue 
	SearchList.push_back(Graph3[node-1][node-1]); //record start node 
	while(!Q.empty())
	{
		Node &tmp = Q.front();
		cout<<node<<" -> "+tmp.getName()<<": "<<tmp.getDist()<<endl; //print out the route and distance 
		int index = tmp.getNo()-1;
		for(int i = index, j = 0; j<N; ++j)
		{
			if(Graph3[i][j].getDist() != 0)
			{
				NodeArray::iterator Find = find(SearchList.begin(), SearchList.end(), Graph3[i][j]);//try find in vector
				if(Find == SearchList.end())
				{  //if not found, push into queue
					Graph3[i][j].setDist(tmp.getDist()+Graph3[i][j].getDist()); //set the distance
					Q.push(Graph3[i][j]); //push into queue 
					SearchList.push_back(Graph3[i][j]); //record in list
				}
			}
		}
		Q.pop();
	}
}

#include "Node.cpp"
#include "Graph_adjList.cpp"

typedef map<Node, map<Node, int> > Graph;
typedef map<Node, int> Map;
typedef vector<Node> Array;

Graph Prim(Graph &graph, Array &NodeArray); //Prim algorithm
Graph Kruskal(Graph &graph, Array &NodeArray); //Kruskal algorithm
void Qsort(vector<pair<Node, pair<Node, int> > > &EdgeArray, int left, int right); //quick sort to sort the edge by weighted
void swap(vector<pair<Node, pair<Node, int> > > &EdgeArray, int i, int j); //swap position
bool HasCircle(Graph &graph, Array &NodeArray); //exam the circle in undirected graph

//main
int main(void)
{
	int num[] = {1,2,3,4,5,6,7,8};
	int matrix[][N]={ 0, 1, 2,-1,-1,-1,-1,-1,
					  1, 0, 4, 5, 7,-1,-1,-1,
				      2, 4, 0,-1, 8,-1, 3, 4,
		         	 -1, 5,-1, 0, 6,-1,-1,-1,
					 -1, 7, 8, 6, 0, 5,-1,-1,
					 -1,-1,-1,-1, 5, 0,-1,-1,
					 -1,-1, 3,-1,-1,-1, 0, 7,
					 -1,-1, 4,-1,-1,-1, 7, 0}; //-1 means no edge, 0 means itself

	Graph_adjList Graph1;
	Array NodeArray;
	Graph1.InitGraph(num, matrix);
	NodeArray = Graph1.getNodeArray();
	Graph graph = Graph1.getGraph(); 
	//test graph------------------------------------------------------------------
	// Graph::iterator iter4, iter5;
	// Map::iterator iter6;
	// for(iter4 = graph.begin();iter4!=graph.end();++iter4)
	// { 
	// 	cout<<iter4->first.getNO()<<" linked with ";
	// 	iter5 = graph.find(iter4->first);
	// 	for(iter6 = iter5->second.begin(); iter6 !=iter5->second.end(); ++iter6)
	// 	{
	// 		//cout<<iter6->first.getNO()<<"+"<<iter6->second<<"  ";
	// 		cout<<iter6->first.getNO()<<" ";
	// 	}
	// 	cout<<endl;
	// }
	//test over------------------------------------------------------------------
	Graph MST = Prim(graph, NodeArray);
	Graph::iterator iter1, iter2;
	Map::iterator iter3;
	//print out result
	cout<<"for Prim:"<<endl;
	for(iter1 = MST.begin();iter1!=MST.end();++iter1)
	{ 
		cout<<iter1->first.getNO()<<" linked with ";
		iter2 = MST.find(iter1->first);
		for(iter3 = iter2->second.begin(); iter3 !=iter2->second.end(); ++iter3)
		{
			cout<<iter3->first.getNO()<<" ";
		}
		cout<<endl;
	}

	Graph MST2 = Kruskal(graph, NodeArray);
	//print out result
	cout<<"for Kruskal:"<<endl;
	for(iter1 = MST2.begin();iter1!=MST2.end();++iter1)
	{ 
		cout<<iter1->first.getNO()<<" linked with ";
		iter2 = MST2.find(iter1->first);
		for(iter3 = iter2->second.begin(); iter3 !=iter2->second.end(); ++iter3)
		{
			cout<<iter3->first.getNO()<<" ";
		}
		cout<<endl;
	}
	return 0;
}
//----------------------------------------------
Graph Prim(Graph &graph, Array &NodeArray)
{
	Graph MST; 
	Array Check;  
	Check.push_back(NodeArray[0]);//choose a node arbitrarily
	Map emptyMap;
	MST.insert(pair<Node, Map>(NodeArray[0],emptyMap)); //put into MST
	Graph::iterator iter1, iter2;
	Map::iterator iter3;
	while(Check.size()<N)
	{	//loop while there still exists nodes which are not in MST 
		Node tmpNode, tmpKey;
		Map tmpMap;
		int least = Inf; 
		for(int i = 0; i < Check.size(); ++i)
		{    //loop for every edge which one end in MST one end not
			iter1 = graph.find(Check[i]);
			for(iter3 = iter1->second.begin(); iter3 != iter1->second.end();++iter3)
			{
				Array::iterator Find = find(Check.begin(), Check.end(), iter3->first);
				if((Find == Check.end()) && least > iter3->second)
				{	
					tmpKey = Check[i];
					tmpNode = iter3->first;
					least = iter3->second;
				}
			} //find least weight
		}
		if(least!=Inf)
		{  //record the node found
			Check.push_back(tmpNode);
			iter2 = MST.find(tmpKey);
			iter2->second.insert(pair<Node, int>(tmpNode, least));
			tmpMap.insert(pair<Node, int>(tmpKey, least));
			MST.insert(pair<Node, Map>(tmpNode, tmpMap));
		}
	}
	return MST; //return MST
}

Graph Kruskal(Graph &graph, Array &NodeArray)
{
	Graph MST; 
	Array Check;
	Array NodeSet;
	vector<pair<Node, pair<Node, int> > > EdgeArray;
	Graph::iterator iter1, iter2, iter4;
	Map::iterator iter3, iter5, iter6;
	for(iter1 = graph.begin();iter1!=graph.end();++iter1)
	{    //get all edge from graph
		for(iter3 = iter1->second.begin();iter3!=iter1->second.end();++iter3)
		{
			Array::iterator Find = find(Check.begin(), Check.end(), iter3->first);
			if((Find == Check.end()))
			{	
				EdgeArray.push_back(make_pair(iter1->first, make_pair(iter3->first, iter3->second)));
				Check.push_back(iter1->first);
			}
		}
	}
	Qsort(EdgeArray, 0, EdgeArray.size()-1); //sort edges by weighted
	//print out sorted result
	// cout<<"After sorting:"<<endl;
	// for(int i =0;i<EdgeArray.size();++i)
	// {
	// 	cout<<EdgeArray[i].first.getNO()<<" "<<EdgeArray[i].second.first.getNO()<<"  "<<EdgeArray[i].second.second<<endl;
	// }
	//-----------------------------------
	for(int i = 0;i<EdgeArray.size();++i)
	{
		//generate graph by adding edge-------------------
		iter2 = MST.find(EdgeArray[i].first);
		if(iter2 == MST.end())
		{  
			Map emptyMap;
			emptyMap.insert(pair<Node, int>(EdgeArray[i].second.first, EdgeArray[i].second.second));
			MST.insert(pair<Node, Map>(EdgeArray[i].first, emptyMap));
			iter4 = MST.find(EdgeArray[i].second.first);
			if(iter4 == MST.end())
			{
				Map emptyMap2;
				emptyMap2.insert(pair<Node, int>(EdgeArray[i].first, EdgeArray[i].second.second));
				MST.insert(pair<Node, Map>(EdgeArray[i].second.first, emptyMap2));
				
			}
			else
			{
				iter4->second.insert(pair<Node, int>(EdgeArray[i].first, EdgeArray[i].second.second));
			}
		}
		else
		{
			iter2->second.insert(pair<Node, int>(EdgeArray[i].second.first, EdgeArray[i].second.second));
			iter4 = MST.find(EdgeArray[i].second.first);
			if(iter4 == MST.end())
			{
				Map emptyMap2;
				emptyMap2.insert(pair<Node, int>(EdgeArray[i].first, EdgeArray[i].second.second));
				MST.insert(pair<Node, Map>(EdgeArray[i].second.first, emptyMap2));	
			}
			else
			{
				iter4->second.insert(pair<Node, int>(EdgeArray[i].first, EdgeArray[i].second.second));
			}
		}
		//---------------------------------------------------------------------------------------------
		//record the edge which has been visited
		NodeSet.push_back(EdgeArray[i].first);
		NodeSet.push_back(EdgeArray[i].second.first);
		sort(NodeSet.begin(), NodeSet.end()); //sort set
		NodeSet.erase(unique(NodeSet.begin(),NodeSet.end()), NodeSet.end()); //remove the reduplicate edges
		vector<Node>::iterator iter;
		for(iter = NodeSet.begin();iter!=NodeSet.end();++iter)
		{
			(*iter).setColor(white);
		}
		if(!HasCircle(MST, NodeSet))
		{   //if there exists no circle after adding the edge, continue loop
			continue;
		}
		else
		{    //if exist any circles, remove the added edge
			iter2 = MST.find(EdgeArray[i].first);
			iter5 = iter2->second.find(EdgeArray[i].second.first);
			iter2->second.erase(iter5);
			iter2 = MST.find(EdgeArray[i].second.first);
			iter6 = iter2->second.find(EdgeArray[i].first);
			iter2->second.erase(iter6);	
		}
	}
	return MST; //return the spanning tree
}

void Qsort(vector<pair<Node, pair<Node, int> > > &EdgeArray, int left, int right)
{
	int i = left,j = 0; //initialize the index
	for(j = left+1; j < right ; ++j)
	{
		if(EdgeArray[j].second.second < EdgeArray[left].second.second)
		{   //increase the index of i, then swap the elements
			swap(EdgeArray, ++i, j);
		}
	}
	swap(EdgeArray, i, left); //swap the position with the pivot element
	if(left<right)
	{
		Qsort(EdgeArray, left, i-1); //recursion for left part
		Qsort(EdgeArray, i+1, right); //recursion for right part
	}
}

void swap(vector<pair<Node, pair<Node, int> > > &EdgeArray, int i, int j)
{
	pair<Node, pair<Node, int> > tmp = EdgeArray[i]; 
	EdgeArray[i] = EdgeArray[j];
	EdgeArray[j] = tmp;
}

bool HasCircle(Graph &graph, Array &NodeArray)
{
	Graph::iterator iter1, iter2;
	Map::iterator iter3;
	queue<int> Q;
	Q.push(0);
	NodeArray[0].setColor(grey); //set color to grey while in queue
	while(!Q.empty())
	{ //loop until queue is empty
		int i = Q.front();
		Q.pop(); //pop out front
		NodeArray[i].setColor(black);
		iter1 = graph.find(NodeArray[i]);
		Map::iterator iter3;
		for(iter3 = iter1->second.begin();iter3!=iter1->second.end();++iter3)
		{
			if(NodeArray[iter3->first.getNO()-1].getColor()==white)
			{  //exam color, if white, enqueue 
				NodeArray[iter3->first.getNO()-1].setColor(grey); //change color
				Q.push(iter3->first.getNO()-1);	
			}
			else if(NodeArray[iter3->first.getNO()-1].getColor() == grey)
			{	//if color is grey before enqueue, it means there exists circles, return true
				return true;
			}
		}
	}
	return false; //else return false
}

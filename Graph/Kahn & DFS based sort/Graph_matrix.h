#ifndef Headers_h_
#include "Headers.h"
#endif
#ifndef Node_h_
#include "Node.h"
#endif

#ifndef Graph_matrix_h
#define Graph_matrix_h
class Graph_matrix
{
	private:
		vector<Node> NodeArray;
		Node adjMatrix[N][N];
	
	public:
		Graph_matrix();
		~Graph_matrix();

		void setNodeArray(int num[]); //store node in array
		void InitGraph(int matrix[][N], int num[], Node Matrix[][N]);
};
#endif
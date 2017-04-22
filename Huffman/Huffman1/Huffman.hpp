#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

typedef char ElemType1;
typedef double ElemType2;

using namespace std;

typedef struct NodeRecord
{
	ElemType1 chars;
	ElemType2 weight;
	friend bool operator<(const NodeRecord &node1, const NodeRecord &node2)
	{
		return node1.weight < node2.weight;
	}
	int leftChild;
	int rightChild;
}Node;

bool SortByWeight(const Node &node1, const Node node2)
{	//sort array
	return node1.weight < node2.weight;
}

#ifndef Huffman
class Huffman
{
	private:
		vector<Node> Data;
		priority_queue<Node> HT;
		map<string, Node> HC;
		vector<ElemType1> Text;

	public:
		Huffman(){cout<<"Huffman tree created."<<endl;} //constructor
		~Huffman(){cout<<"Huffman tree destroyed."<<endl;} //destructor
		//set data
		void setData(ElemType1 chars, ElemType2 weight)
		{
			Node node;
			node.chars = chars;
			node.weight = weight;
			node.leftChild = -1;
			node.rightChild = -1;
			this->Data.push_back(node);
		}
		//get data
		vector<Node> getData()
		{
			return this->Data;
		}
		//build Huffman tree
		void BuildHT()
		{	
			int j = this->Data.size()-1;
			int index = 0;
			vector<Node> tmpData;
			for(int i = 0; i < j; ++i)
			{  
				sort(this->Data.begin(), this->Data.end(), SortByWeight); 
				// for(int k  = 0; k < this->Data.size(); ++k)
				// {
				// 	cout<<this->Data[k].weight<<" ";
				// }
				// cout<<endl;
			// take out first two nodes to build tree
				this->HT.push(this->Data[0]); 
				this->HT.push(this->Data[1]);
				tmpData.push_back(this->Data[0]);
				tmpData.push_back(this->Data[1]);
				Node node;
				node.chars = '\0';
				node.weight = this->Data[0].weight + this->Data[1].weight;
				node.leftChild = index;
				node.rightChild = ++index;
				this->Data.erase(this->Data.begin());
				this->Data.erase(this->Data.begin());
				this->Data.push_back(node);
				++index;
			}
			this->HT.push(this->Data[0]);
			tmpData.push_back(this->Data[0]);
			this->Data = tmpData;
		}
		//return queue
		priority_queue<Node> getHT()
		{
			return this->HT;
		}
		//encode
		void Encode(Node &node, string code, priority_queue<Node> &Tree)
		{
			string left = code, right = code;
			Tree.pop();
			if(node.leftChild != -1)
			{	//add 0 if go left
				left += "0";
				Encode(this->Data[node.leftChild], left, Tree);
			}
			if(node.rightChild != -1)
			{	//otherwise add 1
				right += "1";
				Encode(this->Data[node.rightChild], right, Tree);
			}
			if(node.chars != '\0')
			{
				HC.insert(make_pair(code, node));
			}
		}
		//get map
		map<string, Node> getHC()
		{	
			return this->HC;
		}
		//decode according to text
		vector<ElemType1> Decode(string text)
		{
			Node node = this->HT.top();
			cout<<"text size is "<<text.size()<<endl;
			for(int i = 0;i < text.size(); ++i)
			{	//loop for the text
				if(text[i]=='0')
				{	//go left if 0
					if(node.leftChild != -1)
					{
						//cout<<node.weight<<"->";
						node = this->Data[node.leftChild];
						//cout<<node.weight<<"  ";
						if(node.chars!='\0')
						{
							this->Text.push_back(node.chars);
							//cout<<endl;
							node = this->HT.top();
						}
					}
				}
				if(text[i] == '1')
				{	//go right if 1
					if(node.rightChild != -1)
					{
						// cout<<node.weight<<"->";
						node = this->Data[node.rightChild];
						//cout<<node.weight<<"  ";
						if(node.chars!='\0')
						{
							this->Text.push_back(node.chars);
							//cout<<endl;
							node = this->HT.top();
						}
					}
				}
			}
			return this->Text; //return decoded text
		}	
};
#endif

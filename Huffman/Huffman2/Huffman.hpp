#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <string.h>
#include <cstdlib>
#include <fstream> //file operation

using namespace std;
#define MAX 260  //capacity 
#define BUFF 10  //buffer 
#define _EOF 256 //numbers of characters
typedef struct NodeRecord
{
	int Id;  
	unsigned int Freq; //frequency
	string Code; //huffman code
	NodeRecord *Left, *Right, *Parent;  //two children and one parent
}*Node;

#ifndef Huffman
class Huffman
{
	private:
		Node NodeArray[MAX];  //nodes 
		Node Root; //the root of huffman tree
		int size; //numbers of nodes
		map<int, string> T; //map for char -> huffman code
		fstream inFile, outFile; //two objects of files
		//define the comparison class
		class comp
		{
			public:
				bool operator()(const Node &node1, const Node &node2) const
				{
					return (*node1).Freq > (*node2).Freq; //return true if node1's freq largen than node2
				}

		};
		priority_queue<Node, vector<Node>, comp> Q; //priority queue to store tree
		//set node array
		void setNodeArray()
		{
			int FreqArray[MAX] = {0};
			char c;
			while(!this->inFile.eof())
			{	//while no in the end of file
				this->inFile.get(c); //get the characters
				if(this->inFile.eof())
				{
					break; //break if in the end
				}
				FreqArray[(unsigned char)c]++; //increase the frequency
			}
			//count the numbers of nodes
			int count = 0;
			for(int i = 0; i < MAX;++i)
			{
				if(FreqArray[i] <= 0)
				{
					continue; //skip if zero frequency
				}
				Node node = new NodeRecord(); //new a node
				node->Id = i;
				node->Freq = FreqArray[i];
				node->Code = "";
				node->Left = NULL;
				node->Right = NULL;
				node->Parent = NULL;
				this->NodeArray[count++] = node; //store the node pointer into array
			}
			Node node = new NodeRecord();
			node->Id = _EOF;
			node->Freq = 1;
			node->Code = "";
			node->Left = NULL;
			node->Right = NULL;
			node->Parent = NULL;
			this->NodeArray[count++] = node; //store the eof node
			this->size = count; //store the counting result
		}
		//set huffman codes 
		void setT(const Node node, bool Left)
		{
			//test for left pointer, which can also test for right if like
			if(Left) 
			{	//go left, add 0
				node->Code = node->Parent->Code + "0";
			}
			else
			{	//go right, add 1
				node->Code = node->Parent->Code + "1";
			}
			//if no child, store the code to the map
			if(node->Left == NULL && node->Right == NULL)
			{
				this->T[node->Id] = node->Code;
			}
			else
			{	//set child nodes by recursion
				if(node->Left != NULL)
				{
					setT(node->Left, true);
				}
				if(node->Right != NULL)
				{
					setT(node->Right, false);
				}
			}
		}
		//set priority queue
		void setQ()
		{
			setNodeArray(); //set node array first
			for(int i = 0;i<this->size;++i)
			{
				this->Q.push(this->NodeArray[i]); //enqueue
			}
		}
		//set Huffman tree
		void setHT()
		{
			this->Root = NULL; //initialize root 
			while(!Q.empty())
			{  //loop while not empty
				Node first = Q.top(); //get top node
				Q.pop(); //pop it out
				if(Q.empty())
				{	//break if empty queue
					this->Root = first;
					break;
				}
				Node second = Q.top(); //get another node 
				Q.pop(); 
				Node newNode = new NodeRecord(); 
				newNode->Freq = first->Freq + second->Freq; //parent node
				//choose small one for left child
				if(first->Freq <= second->Freq)
				{	
					newNode->Left = first;
					newNode->Right = second;
				}
				else
				{
					newNode->Left = second;
					newNode->Right = first;
				}
				//set parent pointer
				first->Parent = newNode; 
				second->Parent = newNode; 
				Q.push(newNode); //push into queue
			}
		}
		//set Huffman code
		void setHC()
		{
			if(this->Root == NULL)
			{
				cout<<"Failed to build Huffman tree since no nodes"<<endl;
				exit(1);
			}
			if(Root->Left != NULL)
			{	//go left
				setT(this->Root->Left, true);
			}
			if(Root->Right != NULL)
			{	//go right
				setT(this->Root->Right, false);
			}
		}
		//encode the file
		void setEncode()
		{
			int L, i; //L is length, i for counter
			char in_c; //input char 
			unsigned char out_c, tmp_c; //output char and temperaory char
			string code, out_s; //huffman code and output string
			map<int, string>::iterator iter; //iterator of map
			this->outFile<<this->size<<endl; //input size of tree into output file
			for(iter = this->T.begin(); iter!=this->T.end();++iter)
			{
				outFile<<iter->first<<" "<<iter->second<<endl; //store map into file
			}
			this->inFile.clear(); //clear stream
			this->inFile.seekg(ios::beg); //seek the position
			code.clear();
			while(!this->inFile.eof())
			{	//loop if not EOF
				this->inFile.get(in_c);
				if(this->inFile.eof())
				{
					break;
				}
				iter = this->T.find((unsigned char)in_c); //find Huffman code
				if(iter!=this->T.end())
				{
					code += iter->second; 
				}
				else
				{
					cout<<"Can't encode this character "<<in_c<<endl;
					exit(1);
				}
				L = code.length();
				if(L>BUFF)
				{	//write if large than buffer
					out_s.clear();
					//write Huffman
					for(i = 0; i + 7 < L; i += 8)
					{   //changer every 8-bits code binary code into unsigned char
						out_c = 0;
						for(int j = 0;j < 8; ++j)
						{
							if('0' == code[i+j])
							{
								tmp_c = 0;
							}
							else
							{
								tmp_c = 1;
							}
							out_c += tmp_c<<(7-j);
						}
						out_s += out_c;
					}
					this->outFile<<out_s;
					code = code.substr(i, L-i);
				}
			}
			//add EOF at the end
			iter = this->T.find(_EOF);
			if(iter!=this->T.end())
			{
				code += iter->second;
			}
			else
			{
				cout<<"Can't encode the end of file."<<endl;
				exit(1);
			}
			//deal with the tail
			L = code.length();
			out_c = 0;
			for(i = 0; i < L; ++i)
			{
				if('0'==code[i])
				{
					tmp_c = 0;
				}
				else
				{
					tmp_c = 1;
				}
				out_c += tmp_c<<(7-(i%8));
				if(0 == (i+1)%8 || i == L-1)
				{	//write every 8-bits to file
					this->outFile<<out_c;
					out_c = 0;
				}
			}
		}
		//rebuild the Huffman tree from file
		void rebuildHT()
		{
			string code;
			Node node, tmpNode, newNode;
			//create root node
			this->Root = new NodeRecord();
			this->Root->Left = NULL;
			this->Root->Right = NULL;
			this->Root->Parent = NULL;
			this->inFile>>this->size;
			if(this->size>MAX)
			{
				cout<<"Invalid numbers of node."<<endl;
				exit(1);
			}
			int i, j, id, L;
			for(int i = 0;i < size; ++i)
			{
				this->inFile>>id;
				this->inFile>>code;
				L = code.length();
				node = this->Root;
				for(int j = 0; j < L;++j)
				{
					if('0' == code[j])
					{
						tmpNode = node->Left;
					}
           			else if('1' == code[j])
           			{
           				tmpNode = node->Right;
           			}
                	else
            		{
                		cout<<"Failed to decode, not compatible with huffman code."<<endl;;
                		exit(1);
            		}
            		//if empty, create new node
            		if(tmpNode == NULL)
            		{
            			newNode = new NodeRecord();
                		newNode->Left = NULL;
                		newNode->Right = NULL;
                		newNode->Parent = node;
                		if(j == L-1)
               			{	//for child
                    		newNode->Id = id;
                    		newNode->Code = code;
                		}
                		if('0' == code[j])
                		{	//turn left for 0
                			node->Left = newNode;
                		}
                   		else
                   		{	//oterwise go right
                   			node->Right = newNode;
                   		}
                		tmpNode = newNode;
            		}
            		else if(j == L-1)
            		{	//error in Huffman codes
            			cout<<"Invalid Huffman code."<<endl;
            			exit(1);
            		}
            		else if(tmpNode->Left == NULL && tmpNode->Right == NULL)
            		{	//find wrong way
            			cout<<"Invalid Huffman code."<<endl;
            		}
            		node = tmpNode;
				}
			}
		}
		//decode the file
		void setDecode()
		{
			char in_c;
			unsigned char u_c, flag;
			string out_s;
			bool _eof = false;
			Node node = this->Root;
			out_s.clear();
			this->inFile.get(in_c);
			while(!this->inFile.eof())
			{ 
				this->inFile.get(in_c); //skip last enter
				u_c = (unsigned char)in_c;
				flag = 0x80;
				for(int i = 0; i < 8;++i)
				{
					if(u_c & flag)
					{
						node = node->Right;
					}
					else
					{
						node = node->Left;
					}
					if(node->Left == NULL && node->Right == NULL)
					{
						int id = node->Id;
						if(id == _EOF)
						{
							_eof = true;
							break;
						}
						else
						{	//convert unsigned char to char
							out_s += (char)node->Id;
							node = this->Root;
						}
					}
					flag >>= 1; //shift right
				}
				if(_eof)
				{
					break;
				}
				if(BUFF < out_s.length())
				{
					this->outFile<<out_s;
					out_s.clear();
				}
			}
			if(!out_s.empty())
			{
				this->outFile<<out_s;
			}
		}

	public:
		//construtor
		Huffman(string inFileName, string outFileName)
		{	//two string s input file name and output file name
			cout<<"Huffman is running."<<endl;
			this->inFile.open(inFileName.c_str(), ios::in);
			if(!this->inFile)
			{
				cout<<"Failed to open file: "<<inFileName.c_str()<<endl;
				exit(1);
			}
			this->outFile.open(outFileName.c_str(), ios::out);
			if(!this->outFile)
			{
				cout<<"Failed to open file:"<<outFileName.c_str()<<endl;
				exit(1);
			}
		}
		//destructor
		~Huffman()
		{	//close file
			this->inFile.close();
			this->outFile.close();
			cout<<"Huffman completed."<<endl;
		}
		//driver function
		void Encode()
		{
			setQ();
			setHT();
			setHC();
			setEncode();
		}

		void Decode()
		{
			rebuildHT();
			setDecode();
		}
};
#endif

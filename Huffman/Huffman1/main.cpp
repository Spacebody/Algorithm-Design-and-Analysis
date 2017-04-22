#include "Huffman.hpp"

int main(void)
{
	Huffman HT;
	HT.setData('i', 0.18);
	HT.setData('u', 0.05);
	HT.setData('a', 0.32);
	HT.setData('e', 0.25);
	HT.setData('k', 0.20);
	HT.BuildHT();
	priority_queue<Node> Tree = HT.getHT();
	while(!Tree.empty())
	{
		cout<<Tree.top().weight<<Tree.top().chars<<" "<<Tree.top().leftChild<<" "<<Tree.top().rightChild<<endl;
		Tree.pop();
	}
	cout<<endl;
	
	vector<Node> NodeArray = HT.getData();
	for(int i = 0;i<NodeArray.size();++i)
	{
		cout<<NodeArray[i].weight<<" "<<NodeArray[i].chars<<" "<<NodeArray[i].leftChild<<" "<<NodeArray[i].rightChild<<endl;
	}
	cout<<endl;
	
	Tree = HT.getHT();
	HT.Encode(NodeArray[NodeArray.size()-1], "\0", Tree);
	map<string, Node> HC = HT.getHC();
	map<string, Node>::iterator iter;
	cout<<"char"<<"  code"<<endl;
	for(iter = HC.begin(); iter != HC.end(); ++iter)
	{
		cout<<iter->second.weight<<" -- "<<iter->first<<endl;
	}

	//string text = "0100110010110110101010110011010101";
	string text = "010011001011";
	vector<ElemType1> decodeText = HT.Decode(text); //
	cout<<"Decode text is:"<<endl;
	for(int i = 0; i < decodeText.size(); ++i)
	{
		cout<<decodeText[i];
	}
	cout<<endl;
	return 0;
}
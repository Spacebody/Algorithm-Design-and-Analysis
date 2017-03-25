#include "Headers.h"
#include "Node.h"

	Node::Node(){};
	Node::~Node(){};

	void Node::setNO(int no)
	{
		this->NO = no;
	}

	int Node::getNO()
	{
		return this->NO;
	}

	void Node::setIndegree(int indegree)
	{
		this->indegree = indegree;
	}

	int Node::getIndegree() const
	{
		return this->indegree;
	}

	void Node::setOutdegree(int outdegree)
	{
		this->outdegree = outdegree;
	}

	int Node::getOutdegree() const
	{
		return this->outdegree;
	}

	//alter indegree
	void Node::altIndegree(int x)
	{
		this->indegree += x;
	}

	//alter outdegree
	void Node::altOutdegree(int x)
	{
		this->outdegree += x;
	}

	void Node::setState(bool state)
	{
		this->visit = state;
	}

	bool Node::getState()
	{
		return this->visit;
	}

	void Node::setstateNum(int num)
	{
		this->stateNum = num;
	}

	int Node::getstateNum()
	{
		return this->stateNum;
	}

	bool Node::operator < (const Node &node) const
	{
		return this->NO < node.NO;
	} 
 	
	bool Node::operator == (const Node &node) const
	{
      	return this->NO == node.NO;
    }
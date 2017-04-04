#include "Headers.h"
#include "Node.h"

	Node::Node(){};
	Node::~Node(){};

	void Node::setNO(int no)
	{
		this->NO = no;
	}

	int Node::getNO() const
	{
		return this->NO;
	}

	void Node::setState(bool state)
	{
		this->visit = state;
	}

	bool Node::getState() const
	{
		return this->visit;
	}

	void Node::setColor(int color)
	{
		this->Color = color;
	}

	int Node::getColor() const
	{
		return this->Color;
	}

	bool Node::operator < (const Node &node) const
	{
		return this->NO < node.NO;
	} 
 	
	bool Node::operator == (const Node &node) const
	{
      	return this->NO == node.NO;
    }
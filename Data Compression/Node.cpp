#include "Node.h"

Node::Node()
{
	val = '/';
	parent = nullptr;
	leftchild = nullptr;
	rightchild = nullptr;
}

///fix destructor
Node::~Node()
{
	if (leftchild != nullptr && val == '/')
		delete leftchild;
	if (rightchild != nullptr  && val == '/')
		delete rightchild;
}

 bool ReverseCompare::operator()(const Node* v1, const Node* v2)
 {
	 return v1->count > v2->count;
 }

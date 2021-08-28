#ifndef NODE_H 
#define NODE_H
struct Node
{
	public:
		Node *parent, *leftchild, *rightchild;
		char val;
		bool edge;
		unsigned short int count;
		Node();
		~Node();
};

struct ReverseCompare
{
	bool operator()(const Node* v1, const Node* v2);
};
#endif 
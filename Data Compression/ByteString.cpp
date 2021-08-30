#include "ByteString.h"
using namespace std;

compressor::compressor(string traindata)
{
	unsigned short datasize = unsigned short int(traindata.size());
	for(int i = 0; i < 26; i++)
	{
		letter[i].val = static_cast<char>('a' + i);
		letter[i].count = 0;
	}
	for(char c:traindata)
		letter[c-'a'].count++;
	double entropy=0;
	for(int i = 0; i < 26; i++)
	{
		entropy -= (max(double(letter[i].count), double(1)) / double(datasize)) * log2(max(double(letter[i].count), double(1)) / double(datasize));
	}
	cout << "entropy: " << entropy << endl;

}

void compressor::initializeHuffmanEncoder()
{
	///delete root
	priority_queue<Node*, vector<Node*>, ReverseCompare> HuffmanTree;
	for(int i = 0; i < 26; i++)
	{
		letter[i].count = max(letter[i].count, unsigned short int(1));
		HuffmanTree.push(&letter[i]);
	}

	while (HuffmanTree.size()>1)
	{
		Node *newnode = new Node();
		Node *leftchild, *rightchild;

		leftchild = HuffmanTree.top();
		leftchild->edge = true;
		leftchild->parent = newnode;
		HuffmanTree.pop();

		rightchild = HuffmanTree.top();
		rightchild->edge = false;
		rightchild->parent = newnode;
		HuffmanTree.pop();

		newnode->count = leftchild->count + rightchild->count;
		newnode->leftchild = leftchild;
		newnode->rightchild = rightchild;
		HuffmanTree.push(newnode);
	}
	root = HuffmanTree.top();
	HuffmanTree.pop();
	for(int i = 0; i < 26; i++)
	{
		Node* cur = &letter[i];
		vector<bool> mapval;
		while(cur->parent != nullptr)
		{
			mapval.push_back(cur->edge);
			cur = cur->parent;
		}
		reverse(mapval.begin(), mapval.end());
		decodeletters[static_cast<char>('a' + i)] = mapval;
	}

	for(int i=0; i<26; i++)
	{
		cout << static_cast<char>('a' + i) << ": ";
		for(unsigned int j = 0; j < decodeletters[static_cast<char>('a' + i)].size(); j++)
			cout << decodeletters[static_cast<char>('a' + i)][j];
		cout << endl;
	}
}

pair<vector<bitset<32>>, int> compressor::encode(string s)
{
	cout << "original string size in bytes: " << s.length() << endl;
	vector<bitset<32>> bitarr;
	unsigned int j = 0;
	bitset<32> curbyte;
	for(char c:s)
	{
		for(unsigned int i = 0; i < decodeletters[c].size(); i++)
		{
			curbyte[j] = decodeletters[c][i];
			j++;
			if (j==32)
			{
				bitarr.push_back(curbyte);
				j=0;
			}
		}
	}
	if (j != 0)
		bitarr.push_back(curbyte);
	cout << "new string size in bytes" << " " << bitarr.size() * sizeof(bitset<32>) + sizeof(vector<bitset<32>>) << endl;
	cout << "senseless symbols: " << (32 - j) % 32 << endl;
	return make_pair(bitarr, (32 - j) % 32);
}

string compressor::decode(pair<vector<bitset<32>>, int> text)
{
	string s;
	Node *curnode = root;
	
	for(int i = 0; i < text.first.size() * 32 - text.second; i++)
	{
		bool b = text.first[i/32][i%32];
		if (b)
			curnode = curnode->leftchild;
		else 
			curnode = curnode->rightchild;
		if (curnode->val != '/')
		{
			s += curnode->val;
			curnode = root;
		}
	}
	cout << s << endl;
	return s;
}
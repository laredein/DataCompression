#include "ByteString.h"
using namespace std;

compressor::compressor(string s)
{
	traindata = s;
	datasize = unsigned short int(s.size());
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
		if (letter[i].count != 0)
			entropy -= (double(letter[i].count)/double(datasize)) * log2(double(letter[i].count)/double(datasize));
	}
	cout << "entropy: " << entropy << endl;

}

void compressor::initializeHuffmanEncoder()
{
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

	Node* root = HuffmanTree.top();
	HuffmanTree.pop();
	///delete root;
	///add tree deletion

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
	return make_pair(bitarr, j);
}
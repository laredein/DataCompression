#ifndef BYTESTRING_H 
#define BYTESTRING_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <bitset>
#include <math.h>
#include "timer.h"
#include "Node.h"

using namespace std;

struct compressor
{
	private:
		priority_queue<Node*, vector<Node*>, ReverseCompare> HuffmanTree;
		Node *letter = new Node[26];
		unordered_map<char, vector<bool>> decodeletters;
		string traindata;
		unsigned short int datasize;
	public:
		compressor(string s);
		void initializeHuffmanEncoder();
		pair<vector<bitset<32>>, int> encode(string s);


};

#endif 
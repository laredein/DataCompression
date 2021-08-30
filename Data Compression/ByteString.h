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
		Node *letter = new Node[26];
		unordered_map<char, vector<bool>> decodeletters;
		Node* root = new Node;
	public:
		compressor(string s);
		void initializeHuffmanEncoder();
		pair<vector<bitset<32>>, int> encode(string s);
		string decode(pair<vector<bitset<32>>, int> text);


};

#endif 
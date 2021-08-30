#include <iostream>
#include "ByteString.h"

using namespace std;

int main()
{
    ///resetTime();
    ///showTime();
    compressor test("abbccdddeeeeeeeeeeee");
    test.initializeHuffmanEncoder();
    pair<vector<bitset<32>>, int> encodedtext = test.encode("abbccdddeeeeeeeeeeeeabbccdddeeeeeeeeeeee");
    cout << test.decode(encodedtext) << endl;
}


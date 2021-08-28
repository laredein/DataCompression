#include <iostream>
#include "ByteString.h"

using namespace std;

int main()
{
    ///resetTime();
    ///showTime();
    compressor test("abbccdddeeeeeeeeeeee");
    test.initializeHuffmanEncoder();
    test.encode("abbccdddeeeeeeeeeeeeabbccdddeeeeeeeeeeee");
}


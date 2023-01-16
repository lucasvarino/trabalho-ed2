#ifndef LZ77_H_INCLUDED
#define LZ77_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Triple
{
    int offset;
    int length;
    char next;
    Triple(int offset, int length, char next) : offset(offset), length(length), next(next) {}
};

class LZ77
{
public:
    LZ77(){};
    ~LZ77(){};
    string comprime(string input);
    string descomprime(string comprimida);

private:
    vector<Triple> compress(string input);
};

#endif // LZ77_H_INCLUDED
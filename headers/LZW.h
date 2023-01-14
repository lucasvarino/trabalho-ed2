#ifndef LZW_H_INCLUDED
#define LZW_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class LZW
{

private:
    map<string, int> dictionary;
    int dictSize = 256;

    string vectorToString(const vector<int> &v);
    vector<int> stringToVector(string input);

public:
    LZW();
    ~LZW();
    string comprime(string uncompressed);
    string descomprime(string compressed);
};

#endif // LZW_H_INCLUDED
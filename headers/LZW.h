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
    map<string, int> dicionario;
    int dictSize = 256;

public:
    LZW();
    ~LZW();
    vector<int> comprime(string uncompressed);
    string descomprime(vector<int> comprimida);
    string vectorToString(const vector<int> &v);
    vector<int> stringToVector(string input);
};

#endif // LZW_H_INCLUDED
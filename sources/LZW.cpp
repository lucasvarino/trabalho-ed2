#include "../headers/LZW.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

LZW::LZW()
{
    for (int i = 0; i < 256; i++)
    {
        dictionary[string(1, i)] = i;
    }
}

LZW::~LZW()
{
}

string LZW::vectorToString(const vector<int> &v)
{
    string result;
    for (int i : v)
    {
        result += static_cast<char>(i);
    }
    return result;
}

vector<int> LZW::stringToVector(string input)
{
    vector<int> output;
    for (char c : input)
    {
        output.push_back(c);
    }
    return output;
}

string LZW::comprime(string uncompressed)
{
    string w;
    vector<int> result;
    for (auto c : uncompressed)
    {
        string wc = w + c;
        if (dictionary.count(wc))
        {
            w = wc;
        }
        else
        {
            result.push_back(dictionary[w]);
            dictionary[wc] = dictSize++;
            w = string(1, c);
        }
    }

    if (!w.empty())
    {
        result.push_back(dictionary[w]);
    }
    return this->vectorToString(result);
}

string LZW::descomprime(string compressed)
{
    vector<int> input = this->stringToVector(compressed);
    unordered_map<int, string> dictionary;

    for (int i = 0; i < 256; i++)
    {
        dictionary[i] = string(1, i);
    }

    string w = dictionary[input[0]];
    string result = w;
    string entry;
    for (int i = 1; i < input.size(); i++)
    {
        int k = input[i];

        if (dictionary.count(k))
        {
            entry = dictionary[k];
        }
        else if (k == dictSize)
        {
            entry = w + w[0];
        }
        else
        {
            throw "Erro na descompressão";
        }

        result += entry;

        dictionary[dictSize++] = w + entry[0];

        w = entry;
    }

    return result;
}

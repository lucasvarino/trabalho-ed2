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
        dicionario[string(1, i)] = i;
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

vector<int> LZW::comprime(string comprimir)
{
    // Inicializa o dicionário com caracteres simples
    for (int i = 0; i < 256; i++)
    {
        dicionario[string(1, i)] = i;
    }
    int proximoCodigo = 256;

    string p = "";
    vector<int> codigos;
    for (char c : comprimir)
    {
        string pc = p + c;
        if (dicionario.count(pc))
        {
            p = pc;
        }
        else
        {
            codigos.push_back(dicionario[p]);
            dicionario[pc] = proximoCodigo++;
            p = string(1, c);
        }
    }
    // Adiciona o último conjunto ao vetor de códigos
    if (!p.empty())
    {
        codigos.push_back(dicionario[p]);
    }
    return codigos;
}

string LZW::descomprime(vector<int> compressed)
{
    std::unordered_map<int, std::vector<int>> dictionary;
    for (int i = 0; i < 256; i++)
    {
        dictionary[i] = {i};
    }
    int next_code = 256;
    std::vector<int> decompressed;
    int old_code = compressed[0];
    decompressed.push_back(old_code);
    for (int i = 1; i < compressed.size(); i++)
    {
        int current_code = compressed[i];
        std::vector<int> current_string;
        if (dictionary.count(current_code))
        {
            current_string = dictionary[current_code];
        }
        else
        {
            current_string = dictionary[old_code];
            current_string.push_back(current_string[0]);
        }
        for (int j = 0; j < current_string.size(); j++)
        {
            decompressed.push_back(current_string[j]);
        }
        dictionary[next_code] = dictionary[old_code];
        dictionary[next_code].push_back(current_string[0]);
        next_code++;
        old_code = current_code;
    }
    return this->vectorToString(decompressed);
}

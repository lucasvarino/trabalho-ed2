#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Huffman {
public:
    string compress(const string &text);
    string decompress(const string &compressedText);
    void CriaArvoreHuffman(string text);

private:
    map<char, int> tabelaDeFrequencia(const string &text);
    void geraCodigos(struct MinHeapNode* root, string str);
    map<char, string> encodingTable;
    MinHeapNode* root;
};

#endif
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
    void BuildHuffmanTree(string text);

private:
    map<char, int> frequencyTable(const string &text);
    void printCodes(struct MinHeapNode* root, string str);
    map<char, string> encodingTable;
    MinHeapNode* root;
};

#endif
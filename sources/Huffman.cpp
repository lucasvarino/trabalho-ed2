#include "../headers/Huffman.h"
#include <queue>

struct MinHeapNode
{
    char data;
    int freq;
    MinHeapNode *left, *right;
};

struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

map<char, int> Huffman::tabelaDeFrequencia(const string &text) {
    map<char, int> frequency;
    for (char c : text) {
        frequency[c]++;
    }
    return frequency;
}

void Huffman::geraCodigos(struct MinHeapNode* root, string str)
{
    if (!root)
        return;
    if (root->data != '$')
        encodingTable[root->data] = str;

    geraCodigos(root->left, str + "0");
    geraCodigos(root->right, str + "1");
}

void Huffman::CriaArvoreHuffman(string text)
{
    map<char, int> frequency = tabelaDeFrequencia(text);
    for (auto v : frequency) {
        minHeap.push(new MinHeapNode{ v.first, v.second, nullptr, nullptr });
    }

    while (minHeap.size() != 1)
    {
        MinHeapNode* left = minHeap.top();
        minHeap.pop();

        MinHeapNode* right = minHeap.top();
        minHeap.pop();

        minHeap.push(new MinHeapNode{ '$', left->freq + right->freq, left, right });
    }

    geraCodigos(minHeap.top(), "");
}

string Huffman::compress(const string &text) {
    CriaArvoreHuffman(text);
    string compressedText;

    for (char c : text) {
        compressedText += encodingTable[c];
    }

    return compressedText;
}

string Huffman::decompress(const string &compressedText) {
    MinHeapNode* root = minHeap.top();
    MinHeapNode* current = root;
    string decompressedText = "";

    for (char c : compressedText) {
        if(c == '0')
            current = current->left;
        else
            current = current->right;

        if(current->left == nullptr && current->right == nullptr)
        {
            decompressedText += current->data;
            current = root;
        }
    }
    return decompressedText;
}
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <utility>
#include "../headers/LZ77.h"

using namespace std;

vector<Triple> LZ77::compress(string input)
{
    vector<Triple> result;
    int windowStart = 0;
    int searchStart = 0;
    int matchLength = 0;
    int matchIndex = 0;
    while (searchStart < input.size())
    {
        matchLength = 0;
        for (int i = 0; i < windowStart; i++)
        {
            int j = 0;
            while (input[i + j] == input[searchStart + j] && (i + j) < input.size() && (searchStart + j) < input.size())
            {
                j++;
                if (j > matchLength)
                {
                    matchLength = j;
                    matchIndex = i;
                }
            }
        }
        if (matchLength == 0)
        {
            result.push_back(Triple(0, 0, input[searchStart]));
            searchStart++;
            windowStart++;
        }
        else
        {
            result.push_back(Triple(windowStart - matchIndex, matchLength, input[searchStart + matchLength]));
            searchStart += matchLength;
            windowStart += matchLength;
        }
    }
    return result;
}

string LZ77::comprime(string input)
{
    vector<Triple> comprimida = compress(input);
    string output = "";
    for (int i = 0; i < comprimida.size(); i++)
    {
        output += "(" + to_string(comprimida[i].offset) + "," + to_string(comprimida[i].length) + "," + comprimida[i].next + ")";
    }
    return output;
}

string LZ77::descomprime(string comprimida)
{
    string output = "";
    int i = 0;
    // Enquanto a posição atual na string comprimida for menor do que o tamanho total da string
    while (i < comprimida.size())
    {
        int distance = 0;
        int length = 0;
        char character = '\0';
        i++; // Pula o '('
        // Enquanto o caractere atual for diferente de ','
        while (comprimida[i] != ',')
        {
            distance = distance * 10 + comprimida[i] - '0'; // Calcula a distância
            i++;
        }
        i++;
        // Enquanto o caractere atual for diferente de ','
        while (comprimida[i] != ',')
        {
            length = length * 10 + comprimida[i] - '0'; // Calcula o comprimento
            i++;
        }
        i++;
        // Se a posição atual for menor do que o tamanho total da string e o caractere atual for diferente de ')'
        if (i < comprimida.size() && comprimida[i] != ')')
        {
            character = comprimida[i]; // Armazena o caractere
            i++;
        }
        // Se o comprimento for igual a 0
        if (length == 0)
        {
            output += character; // Adiciona o caractere ao output
        }
        else
        {
            // Adiciona ao output a substring encontrada na distância especificada, por comprimento vezes
            for (int j = 0; j < length; j++)
            {
                if (output.size() - distance < output.size())
                {
                    output += output[output.size() - distance];
                }
            }
            if (character != '\0')
            {
                output += character; // Adiciona o caractere ao output
            }
        }
        i++;
    }
    return output;
}
#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

struct RegistroHash {
    string productId;
    int qtdReviews;
};

class Hash
{
    private:
        int tam;
        RegistroHash *vetor;
        int m_linha;

        int hash1(long long chave);
        int hash2(long long chave);
        long long transformaChave(string chave);

    public:
        Hash(int tamanho);
        Hash();
        ~Hash();
        

        int hash(long long chave, int i);
        void insert(string chave, RegistroHash *registro);
        void search(string chave);
        RegistroHash *getVetor() {return vetor;};
        int getTam() {return tam;};
};










#endif // HASH_H_INCLUDED
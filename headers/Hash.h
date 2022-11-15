#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

typedef struct RegistroHash{
    string productId;
    int qtdReviews;
};

class Hash
{
    private:
        int tam;
        RegistroHash *vetor;
        int m_linha;

        int hash1(int chave);
        int hash2(int chave);
        int transformaChave(string chave);

    public:
        Hash();
        ~Hash();
        

        int hash(int chave, int i);
        void insert(string chave, RegistroHash *registro);
        void search(string chave);
        RegistroHash *getVetor() {return vetor;};
        int getTam() {return tam;};
};










#endif // HASH_H_INCLUDED
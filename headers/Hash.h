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
        int tam; // tamanho da tabela
        RegistroHash *vetor; // vetor de registros
        int m_linha; // m_linha utilizado na função de hash 2

        int hash1(long long chave); // Função de Hash 1
        int hash2(long long chave); // Função de Hash 2
        long long transformaChave(string chave); // Transforma a chave em um número único

    public:
        Hash(int tamanho); // Construtor
        Hash(); 
        ~Hash(); // Destrutor
        

        int hash(long long chave, int i); // Função de Hash
        void insert(string chave, RegistroHash *registro); // Insere um registro na tabela
        void search(string chave); // Busca um registro na tabela
        RegistroHash *getVetor() {return vetor;}; // Retorna o vetor de registros
        int getTam() {return tam;}; // Retorna o tamanho da tabela
        static void quickSortHash(RegistroHash *vetor, int inicio, int fim); // Ordena o vetor de registros utilizando o melhor algoritmo da etapa 2
};










#endif // HASH_H_INCLUDED
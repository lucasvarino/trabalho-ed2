#include "../headers/Hash.h"
#include "../headers/ProductReview.h"
#include "../headers/Sort.h"

#include <iostream>
#include <string>

using namespace std;


//Funções Hash

Hash::Hash(){
}
Hash::~Hash(){
}

int  Hash::transformaChave(string chave){
    int soma = 0;
    for(int i = 0; i < chave.length(); i++){
        soma += (int)chave[i];
    }
    return soma;
}
int Hash::hash1(int chave){
    return chave % tam;
}
int Hash::hash2(int chave){
    return 1+(chave % m_linha);
}
int Hash::hash(int chave, int i){
    return (hash1(chave) + i*hash2(chave)) % tam;
}
void Hash::insert(string chave, RegistroHash *registro){
    int i = 0;
    int pos = hash(transformaChave(chave), i);
    while(vetor[pos].productId != ""){
        if(vetor[pos].productId == chave){
            vetor[pos].qtdReviews++;
            return;
        }
        i++;
        pos = hash(transformaChave(chave), i);
    }
    vetor[pos] = *registro;
}

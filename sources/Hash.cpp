#include "../headers/Hash.h"
#include "../headers/ProductReview.h"
#include "../headers/Sort.h"

#include <iostream>
#include <string>
#include <math.h>

using namespace std;


//Funções Hash

bool verificaPrimo(int tamanho) { //Verifica se o número é primo
    int div = 0;
    for(int aux = 2 ; aux<= sqrt(tamanho) ; aux++)
        if(tamanho % aux == 0)
            div++;

    if(div==0)
        return true;
    else
        return false;
}

int encontraPrimoProximo(int tamanho) {//Encontra o próximo primo
    if(verificaPrimo(tamanho))
        return tamanho;
    
    return encontraPrimoProximo(tamanho+1);
}

Hash::Hash(int tamanho) {///Construtor
    int primo = encontraPrimoProximo(tamanho);
    
    this->tam = primo;
    this->m_linha = primo - 1;
    this->vetor = new RegistroHash[this->tam];
}


Hash::~Hash(){  //Destrutor
    delete [] vetor;
}

long long Hash::transformaChave(string chave){  //Transforma a chave em um número
    long long soma = 0;
    for(unsigned int i = 0; i < chave.length(); i++){
        soma += (int)chave[i] * pow(31, i);
    }
    return soma;
}

int Hash::hash1(long long chave){
    return chave % tam;
}

int Hash::hash2(long long chave){
    return 1+(chave % m_linha);
}

int Hash::hash(long long chave, int i){
    return (hash1(chave) + i * hash2(chave)) % tam;
}

void Hash::insert(string chave, RegistroHash *registro){    //Insere um registro na tabela
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

void Hash::search(string chave){    //Busca um registro na tabela através da chave
    int i = 0;
    int pos = hash(transformaChave(chave), i);
    while(vetor[pos].productId != ""){
        if(vetor[pos].productId == chave){
            cout << "Produto: " << vetor[pos].productId << " - Qtd Reviews: " << vetor[pos].qtdReviews << endl;
            return;
        }
        i++;
        pos = hash(transformaChave(chave), i);
    }
    cout << "Produto não encontrado" << endl;
}


void Hash::quickSortHash(RegistroHash *vetor, int inicio, int fim){
    int i = inicio;
    int j = fim;
    RegistroHash aux;
    RegistroHash pivo = vetor[(inicio + fim) / 2];

    while(i <= j){
        while(vetor[i].qtdReviews > pivo.qtdReviews)
            i++;
        while(vetor[j].qtdReviews < pivo.qtdReviews)
            j--;
        if(i <= j){
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    }
    if(j > inicio)
        quickSortHash(vetor, inicio, j);
    if(i < fim)
        quickSortHash(vetor, i, fim);
}

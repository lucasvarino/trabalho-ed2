#include "../headers/Sort.h"
#include "../headers/ProductReview.h"

#include <iostream>
#include <string>

using namespace std;

    // Funções de Ordenação

void Sort::mergeSort(ProductReview *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

    // Funções Auxiliares

void Sort::merge(ProductReview *vetor, int inicio, int meio, int fim) { // Função de Merge

    //Declarando variaveis auxiliares   
    int i, j, k, tam; 
    tam = meio - inicio + 1;
    i = 0;
    j = meio + 1;
    k = 0;

    // Criação do vetor auxiliar alocado dinamicamente
    ProductReview *aux = new ProductReview[fim - inicio + 1];  

    // Processo de separação dos vetores, e posteriormente a junção ordenada dos mesmos
    while (i < tam && j <= fim) {   
        if (vetor[inicio + i].getUserId() < vetor[j].getUserId()) {
            aux[k] = vetor[inicio + i];
            i++;
        } else {
            aux[k] = vetor[j];
            j++;
        }
        k++;
    }

    while (i < tam) {
        aux[k] = vetor[inicio + i];
        k++;
        i++;
    }

    while (j <= fim) {
        aux[k] = vetor[j];
        k++;
        j++;
    }

    for (i = inicio; i <= fim; i++) {
        vetor[i] = aux[i - inicio];
    }

    delete[] aux;
}           
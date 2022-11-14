#include "../headers/Sort.h"
#include "../headers/ProductReview.h"

#include <iostream>
#include <string>

using namespace std;

    // Funções de Ordenação

void Sort::mergeSort(ProductReview *vetor, int inicio, int fim) {
    this->comparacoes = 0;
    this->trocas = 0;
    this->tempo = 0;


    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

Sort::Sort() {
    this->comparacoes = 0;
    this->trocas = 0;
    this->tempo = 0;
}
Sort::~Sort() {
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

void Sort::quickSort(ProductReview *vetor, int inicio, int fim) {
    high_resolution_clock::time_point start = high_resolution_clock::now();
    int i, j, meio;
    ProductReview pivo, aux;

    i = inicio;
    j = fim;
    meio = (int) ((i + j) / 2);
    pivo = vetor[meio];

    do {
        while (vetor[i].getUserId() < pivo.getUserId()) i = i + 1;
        while (vetor[j].getUserId() > pivo.getUserId()) j = j - 1;
        this->comparacoes++;
        if (i <= j) {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            this->trocas++;
            i = i + 1;
            j = j - 1;
        }
    } while (j > i);

    if (inicio < j) quickSort(vetor, inicio, j);
    if (i < fim) quickSort(vetor, i, fim);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    this->tempo = duration_cast<duration<double>>(end - start).count();
}

void Sort::insertionSort(ProductReview *vetor, int inicio, int fim) //Utilizamos insertionSort pois ele é eficiente em arrays pequenos
{
    //Adaptamos o algoritmo pois agora vamos ordenar subarrays e não o array inteiro
    for(int i = inicio + 1; i < fim; i++)
    {
        int j = i+1;
        ProductReview pivo = vetor[j];
        while(j > inicio && pivo.getUserId() < vetor[j-1].getUserId())
        {
            vetor[j] = vetor[j-1];
            this->trocas++;
            j--;
        }
        this->comparacoes++;
        vetor[j] = pivo;
    }
}

//3° Algoritmo Escolhido - TimSort
void Sort::timSort(ProductReview *vetor, int n)
{
    this->comparacoes = 0;
    this->trocas = 0;
    this->tempo = 0;


    int tamSubArray = 32; // tamanho do subarray
    
    for (int i = 0; i < n; i += tamSubArray) // percorre o vetor de tamSubArray em tamSubArray
        insertionSort(vetor, i, min((i+tamSubArray-1), (n-1))); //ordena os subarrays de tamanho 32
 
    for (int tam = tamSubArray; tam < n; tam = 2 * tam) //
    {
        for (int esquerda = 0; esquerda < n; esquerda += 2 * tam)
        {
            int meio = esquerda + tam - 1;
            int direita = min((esquerda + 2*tam - 1), (n-1)); // pega o menor valor entre o tamanho do vetor e o tamanho do subarray

            if(meio < direita)
                this->merge(vetor, esquerda, meio, direita); //Utiliza-se o Merge já implementado para juntar os subarrays
        }
    }
}




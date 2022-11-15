#include "../headers/Sort.h"
#include "../headers/ProductReview.h"

#include <iostream>
#include <string>

using namespace std;

// Funções de Ordenação

void Sort::mergeSort(ProductReview *vetor, int inicio, int fim, int *contador)
{

    if (contador == 0)
    {
        this->comparacoes = 0;
        this->trocas = 0;
        this->tempo = 0;
    }

    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        mergeSort(vetor, inicio, meio, contador + 1);
        mergeSort(vetor, meio + 1, fim, contador + 1);
        merge(vetor, inicio, meio, fim);
    }
}

Sort::Sort()
{
    this->comparacoes = 0;
    this->trocas = 0;
    this->tempo = 0;
}
Sort::~Sort()
{
}

// Funções Auxiliares

void Sort::merge(ProductReview *vetor, int inicio, int meio, int fim)
{ // Função de Merge

    // Declarando variaveis auxiliares
    int i, j, k, tam;
    tam = meio - inicio + 1;
    i = 0;
    j = meio + 1;
    k = 0;

    // Criação do vetor auxiliar alocado dinamicamente
    ProductReview *aux = new ProductReview[fim - inicio + 1];

    // Processo de separação dos vetores, e posteriormente a junção ordenada dos mesmos
    while (i < tam && j <= fim)
    {
        if (vetor[inicio + i].getUserId() < vetor[j].getUserId())
        {
            aux[k] = vetor[inicio + i];

            i++;
        }
        else
        {
            aux[k] = vetor[j];
            j++;
        }
        k++;
        this->comparacoes++;
    }

    while (i < tam)
    {
        aux[k] = vetor[inicio + i];
        k++;
        i++;
    }

    while (j <= fim)
    {
        aux[k] = vetor[j];
        k++;
        j++;
    }

    for (i = inicio; i <= fim; i++)
    {
        vetor[i] = aux[i - inicio];
        this->trocas++;
    }

    delete[] aux;
}

// Implementando o QuickSort
void Sort::quickSort(ProductReview *vetor, int inicio, int fim)
{
    high_resolution_clock::time_point start = high_resolution_clock::now(); // definindo tempo inicial
    int i, j, meio;
    ProductReview pivo, aux;

    i = inicio;
    j = fim;
    meio = (int)((i + j) / 2);
    pivo = vetor[meio];

    do
    {
        while (vetor[i].getUserId() < pivo.getUserId())
            i = i + 1;
        while (vetor[j].getUserId() > pivo.getUserId())
            j = j - 1; // Compara se as posições são maiores ou menores que o pivo
        this->comparacoes++;
        if (i <= j)
        { // Se a posição i for menor ou igual a posição j, então troca os valores
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            this->trocas++;
            i = i + 1;
            j = j - 1;
        }
    } while (j > i);

    if (inicio < j)
        quickSort(vetor, inicio, j); // Se a posição inicial for menor que a posição j, então chama a função novamente
    if (i < fim)
        quickSort(vetor, i, fim);                                         // Se a posição i for menor que a posição final, então chama a função novamente
    high_resolution_clock::time_point end = high_resolution_clock::now(); // definindo tempo final
    this->tempo = duration_cast<duration<double>>(end - start).count();   // calculando tempo total
}

void Sort::insertionSort(ProductReview *vetor, int inicio, int fim) // Utilizamos insertionSort pois ele é eficiente em arrays pequenos
{
    // Adaptamos o algoritmo apresentado em sala pois agora vamos ordenar subarrays e não o array inteiro
    for (int i = inicio + 1; i < fim; i++)
    {
        int j = i + 1;
        ProductReview pivo = vetor[j];
        while (j > inicio && pivo.getUserId() < vetor[j - 1].getUserId()) // Compara se as posições são maiores ou menores que o pivo
        {
            vetor[j] = vetor[j - 1]; // Se a posição for maior que o pivo, então troca os valores
            this->trocas++;
            j--;
        }
        this->comparacoes++;
        vetor[j] = pivo;
    }
}

// 3° Algoritmo Escolhido - TimSort
void Sort::timSort(ProductReview *vetor, int n)
{
    // Setando as métricas para 0
    this->comparacoes = 0;
    this->trocas = 0;
    this->tempo = 0;

    int tamSubArray = 32; // tamanho do subarray

    for (int i = 0; i < n; i += tamSubArray)                          // percorre o vetor de tamSubArray em tamSubArray
        insertionSort(vetor, i, min((i + tamSubArray - 1), (n - 1))); // ordena os subarrays de tamanho 32

    for (int tam = tamSubArray; tam < n; tam = 2 * tam) //
    {
        for (int esquerda = 0; esquerda < n; esquerda += 2 * tam)
        {
            int meio = esquerda + tam - 1;
            int direita = min((esquerda + 2 * tam - 1), (n - 1)); // pega o menor valor entre o tamanho do vetor e o tamanho do subarray

            if (meio < direita)
                this->merge(vetor, esquerda, meio, direita); // Utiliza-se o Merge já implementado para juntar os subarrays
        }
    }
}

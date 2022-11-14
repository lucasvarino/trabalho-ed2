#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include "ProductReview.h"

#include <iostream>
#include <string>

using namespace std;

// Classe responsável pelos metodos de ordenação
class Sort
{
    private:
        // Variáveis
        int comparacoes;
        int trocas;
        double tempo;

        // Funções Auxiliares
        void merge(ProductReview *vetor, int inicio, int meio, int fim);
        
    public:
        // Funções Get
        int getComparacoes() {return comparacoes;};     
        int getTrocas() {return trocas;};
        double getTempo() {return tempo;};

        // Funções Set
        void setComparacoes(int comparacoes){this->comparacoes = comparacoes;};
        void setTrocas(int trocas) {this->trocas = trocas;};
        void setTempo(double tempo) {this->tempo = tempo;};   
        
        //Funções de Ordenação
        void mergeSort(ProductReview *vetor, int inicio, int fim);
        
};


#endif // SORT_H_INCLUDED
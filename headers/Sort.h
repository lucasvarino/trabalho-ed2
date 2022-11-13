#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include "ProductReview.h"

#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Sort
{
    private:
        int comparacoes;
        int trocas;
        double tempo;
        void merge(ProductReview *vetor, int inicio, int meio, int fim);
    public:
    //constructor
        Sort();
    //destructor
        ~Sort();
        void mergeSort(ProductReview *vetor, int inicio, int fim);
        void quickSort(ProductReview *vetor, int inicio, int fim);
        int getComparacoes(){return this->comparacoes;};
        int getTrocas(){return this->trocas;};
        double getTempo(){return this->tempo;};
        void setComparacoes(int comparacoes){this->comparacoes = comparacoes;};
        void setTrocas(int trocas){this->trocas = trocas;};
        void setTempo(double tempo){this->tempo = tempo;};
        
};


#endif // SORT_H_INCLUDED
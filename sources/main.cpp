#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "../headers/ProductReview.h"
#include "../headers/Sort.h"
#include "../headers/Hash.h"

#define FILE_NAME "ratings_Electronics"

using namespace std;
using namespace std::chrono;

RegistroHash *createTable(int n){
    

}
void createBinary(string &path)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    string dirBin = path + FILE_NAME + ".bin";
    string dirCsv = path + FILE_NAME;
    
    ifstream arqBin(dirBin, ios::in);

    if (arqBin.is_open()) {
        cout << "O arquivo binário já foi criado." << endl; 
        return;
    }
    cout << "Criando arquivo binário..." << endl;
    ProductReview::createBinary(dirCsv);
    high_resolution_clock::time_point fim = high_resolution_clock::now();

    cout << "Arquivo binário criado." << endl << "Tempo gasto para a criação: " << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
    
}
Sort* sort(ProductReview *vet, int n, int methodId){
    Sort *sort = new Sort();
    switch (methodId)
    {
    case 0:
        sort->quickSort(vet, 0, n-1);
        break;
    case 1:
        sort->mergeSort(vet, 0, n-1);
        break;
    case 2:
        sort->timSort(vet, n);
        break;
    default:
        break;
    }   
    return sort;
}

void gerarMetricas(int methodId) {
    int tamConjuntos[5] = {1000, 50000, 100000, 500000, 1000000};
    int qtdConjuntos = 3;
    ProductReview pr;

    int mediaComparacoes = 0;
    int mediaTrocas = 0;
    double mediaTempo = 0;

    ofstream arqTxt("output.txt", ios::out | ios::app);
    arqTxt << "---------------------" << endl;
    arqTxt << "Método " << methodId << endl;
    arqTxt << "---------------------" << endl;
    arqTxt << endl << endl;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < qtdConjuntos; j++)
        {
            high_resolution_clock::time_point inicio = high_resolution_clock::now();

            ProductReview *conjunto = pr.import(tamConjuntos[i]);
            Sort *metricas = sort(conjunto, tamConjuntos[i], methodId);

            high_resolution_clock::time_point fim = high_resolution_clock::now();
            metricas->setTempo(duration_cast<duration<double>>(fim - inicio).count());

            mediaComparacoes += metricas->getComparacoes();
            mediaTrocas += metricas->getTrocas();
            mediaTempo += metricas->getTempo();

            arqTxt << "Conjunto de Tamanho: " << tamConjuntos[i] << endl;
            arqTxt << "Comparacoes: " << metricas->getComparacoes() << endl;
            arqTxt << "Trocas: " << metricas->getTrocas() << endl;
            arqTxt << "Tempo: " << metricas->getTempo() << endl;
            arqTxt << endl;

            delete [] conjunto;
            delete metricas;
        }

        arqTxt << endl;
        arqTxt << "Media de Comparacoes: " << mediaComparacoes/qtdConjuntos << endl;
        arqTxt << "Media de Trocas: " << mediaTrocas/qtdConjuntos << endl;
        arqTxt << "Media de Tempo: " << mediaTempo/qtdConjuntos << endl;
        arqTxt << "---------------------------------" << endl;

        mediaComparacoes = 0;
        mediaTrocas = 0;
        mediaTempo = 0;
        
    }
    

}

int main(int, char**) {
    string path = "./";
    createBinary(path);

    cout << "Seleciona o método"<<endl<<"0 - Quick Sort"<<endl<<"1 - Merge Sort"<<endl << "2 - Tim Sort" << endl;
    int metodo;
    cin >> metodo;
    gerarMetricas(metodo);
    
    
}

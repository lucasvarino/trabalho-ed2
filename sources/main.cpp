#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "../headers/ProductReview.h"
#include "../headers/Sort.h"

#define FILE_NAME "ratings_Electronics"

using namespace std;
using namespace std::chrono;

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
void sort(ProductReview *vet, int n, int methodId){
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
    cout << "Comparacoes: " << sort->getComparacoes() << endl;
    cout << "Trocas: " << sort->getTrocas() << endl;
    cout << "Tempo: " << sort->getTempo() << endl;
    delete sort;
}

int main(int, char**) {
    string path = "./";
    createBinary(path);

    ProductReview* pr = new ProductReview("", "", 0.0, "");
    ProductReview* produtos = pr->import(1000000); //5737229 3953
    ProductReview *produtos2 = new ProductReview[1000000];

    for (int i = 0; i < 1000000; i++)
    {
        produtos2[i] = produtos[i];
    }
    

    Sort s;
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    s.mergeSort(produtos, 0, 999999);
    high_resolution_clock::time_point fim = high_resolution_clock::now();
    cout << "Tempo gasto MergeSort " << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;

    inicio = high_resolution_clock::now();
    s.timSort(produtos2, 1000000);
    fim = high_resolution_clock::now();
    cout << "Tempo gasto TimSort " << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;

    cout << "Seleciona o método"<<endl<<"0 - Quick Sort"<<endl<<"1 - Merge Sort"<< "2- Tim Sort"<<endl;
    int metodo;
    cin >> metodo;
    sort(produtos, 10, metodo);
    
    
}

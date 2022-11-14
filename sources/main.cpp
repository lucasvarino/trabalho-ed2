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
    ProductReview* produtos = pr->import(10); //5737229 3953
    for (int i = 0; i < 10; i++) {
        produtos[i].print();
    }
    cout << "Seleciona o método"<<endl<<"0 - Quick Sort"<<endl<<"1 - Merge Sort"<<endl;
    int metodo;
    cin >> metodo;
    sort(produtos, 10, metodo);
    
    
}

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "ProductReview.h"

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

int main(int, char**) {
    string path = "./";
    createBinary(path);

    ProductReview* pr = new ProductReview("", "", 0.0, "");
    ProductReview* produtos = pr->getReview(5737229); //5737229 3953
    produtos->print();
    // ProductReview* prod1 = new ProductReview("1", "1", 5.0, "10/10/2022");
    // prod1->print();
}

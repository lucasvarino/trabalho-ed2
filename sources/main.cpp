#include <iostream>
#include <string>
#include <fstream>
#include "ProductReview.h"

#define FILE_NAME "ratings_Electronics"

using namespace std;

void createBinary(string &path)
{
    string dirBin = path + FILE_NAME + ".bin";
    string dirCsv = path + FILE_NAME;
    
    ifstream arqBin(dirBin, ios::in);

    if (arqBin.is_open()) {
        cout << "O arquivo binário já foi criado." << endl; 
        return;
    }
    
    ProductReview::createBinary(dirCsv);
    
}

int main(int, char**) {
    string path = "./";
    createBinary(path);

    ProductReview* pr = new ProductReview("", "", 0.0, "");
    ProductReview* produtos = pr->import(10);
    // ProductReview* prod1 = new ProductReview("1", "1", 5.0, "10/10/2022");
    // prod1->print();
}

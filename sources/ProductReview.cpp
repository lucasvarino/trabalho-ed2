#include "ProductReview.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ProductReview::ProductReview(string user_id, string product_id, float rating, string timestamp)
{
    this->user_id = user_id;
    this->product_id = product_id;
    this->rating = rating;
    this->timestamp = timestamp; // Validar a possibilidade de converter o timestamp
}

ProductReview::~ProductReview()
{
}

void ProductReview::print()
{
    cout << "- Product Review -" << endl
         << endl;
    cout << "User id: " << this->user_id << endl;
    cout << "Product id: " << this->product_id << endl;
    cout << "Rating: " << this->rating << endl;
    cout << "Timestamp: " << this->timestamp << endl;
}

void ProductReview::createBinary(string dirCsv) //TODO: Mudar os parâmetros da função pra receber apenas diretório do arquivo
{
    ifstream arqCsv(dirCsv + ".csv", ios::in);
    ofstream arqBin(dirBin + ".bin", ios::out | ios::app | ios::binary);

    string user_idAux;
    string product_idAux;
    string ratingAux;
    string timestampAux;

    while (!arqCsv.eof())
    {
        getline(arqCsv, user_idAux, ',');
        getline(arqCsv, product_idAux, ',');
        getline(arqCsv, ratingAux, ',');
        getline(arqCsv, timestampAux, '\n');

        if(arqBin.is_open()) 
        {
            arqBin.write(reinterpret_cast<const char*>(user_idAux.c_str()), user_idAux.length());
            arqBin.write(reinterpret_cast<const char*>(product_idAux.c_str()), product_idAux.length());
            arqBin.write(reinterpret_cast<const char*>(&ratingAux), sizeof(float));
            arqBin.write(reinterpret_cast<const char*>(timestampAux.c_str()), timestampAux.length());
            
        } else {
            cout << "ERRO: O arquivo nao pode ser aberto!" << endl;
        }

    }

    arqCsv.close();
}

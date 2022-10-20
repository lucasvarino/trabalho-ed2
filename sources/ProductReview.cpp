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

void ProductReview::lerArquivo(string dirCsv, string dirBin)
{
    ifstream arqCsv(dirCsv);
    ofstream arqBin(dirBin, ios::out | ios::app | ios::binary);

    string user_idAux;
    string product_idAux;
    string ratingAux;
    string timestampAux;

    if (arqCsv.is_open())
    {

        getline(arqCsv, user_idAux);
        // getline(arqCsv, product_idAux, ',');
        // getline(arqCsv, ratingAux, ',');
        // getline(arqCsv, timestampAux, ',');


        cout << "teste" << endl;
        
        // ProductReview *pr = new ProductReview(user_idAux, product_idAux, stof(ratingAux), timestampAux);
        // pr->print();
    }
}

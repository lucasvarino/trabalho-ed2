#include "ProductReview.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

ProductReview::ProductReview(string user_id, string product_id, float rating, string timestamp)
{
    this->user_id = user_id;
    this->product_id = product_id;
    this->rating = rating;
    this->timestamp = timestamp; // Validar a possibilidade de converter o timestamp
}

ProductReview::ProductReview() {

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

ProductReview* ProductReview::import(int n)
{
    fstream arq("ratings_Electronics.bin", ios::in | ios::binary);

    if(!arq.is_open())
    {
        cout << "O arquivo binário ainda não foi criado" << endl;
        return nullptr;
    }

    arq.seekg(0);

    // Numero de Registros - 7824483

    char userIdAux[15];
    char productIdAux[11];
    float ratingAux;
    char timestampAux[11];

    for (int i = 0; i < n; i++)
    {
        arq.read(userIdAux, 14);
        arq.read(productIdAux, 10);
        arq.read(reinterpret_cast<char*>(&ratingAux), sizeof(float));
        arq.read(timestampAux, 10);

        userIdAux[14] = '\0';
        productIdAux[10] = '\0';
        timestampAux[10] = '\0';    
        ProductReview pr(userIdAux, productIdAux, ratingAux, timestampAux);

        pr.print();   
    }
    



    return nullptr;
}

void ProductReview::createBinary(string dirCsv)
{
    ifstream arqCsv(dirCsv + ".csv", ios::in);
    ofstream arqBin(dirCsv + ".bin", ios::out | ios::app | ios::binary);

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

        float ratingFloat = stof(ratingAux);

        if(user_idAux.length() < 14) {
            user_idAux = user_idAux + '\0';
        }

        // ProductReview pr(user_idAux, product_idAux, ratingFloat, timestampAux);

        if(arqBin.is_open()) 
        {
            arqBin.write(reinterpret_cast<const char*>(user_idAux.c_str()), user_idAux.length());
            arqBin.write(reinterpret_cast<const char*>(product_idAux.c_str()), product_idAux.length());
            arqBin.write(reinterpret_cast<const char*>(&ratingFloat), sizeof(float));
            arqBin.write(reinterpret_cast<const char*>(timestampAux.c_str()), timestampAux.length());
            
        } else {
            cout << "ERRO: O arquivo nao pode ser aberto!" << endl;
        }
    }

    arqCsv.close();
}

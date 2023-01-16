#include "../headers/ProductReview.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <random>

#define TOTAL_REGISTROS 7824483 // Total de registros no arquivo .csv

using namespace std;

ProductReview::ProductReview(string user_id, string product_id, float rating, string timestamp)
{
    this->user_id = user_id;
    this->product_id = product_id;
    this->rating = rating;
    this->timestamp = timestamp;
}

ProductReview::ProductReview()
{
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

ProductReview *ProductReview::getProductReview(int indice)
{
    fstream arq("ratings_Electronics.bin", ios::in | ios::binary);

    if (!arq.is_open())
    {
        cout << "O arquivo binário ainda não foi criado" << endl;
        return nullptr;
    }

    arq.seekg(indice * (21 + 10 + sizeof(float) + 10)); // Soma dos tamanhos dos atributos (user_id, product_id, rating, timestamp)
    // É necessário fazer a soma dos tamanhos dos atributos para saber quando termina um registro e começa o outro

    char *userIdAux = new char[21]; // Alocação como char
    char *productIdAux = new char[10];
    float ratingAux;
    char *timestampAux = new char[10];

    arq.read(reinterpret_cast<char *>(userIdAux), 21); // Lendo o registro
    arq.read(reinterpret_cast<char *>(productIdAux), 10);
    arq.read(reinterpret_cast<char *>(&ratingAux), sizeof(float));
    arq.read(reinterpret_cast<char *>(timestampAux), 10);

    userIdAux[21] = '\0'; // Adicionando o caractere de fim de string
    productIdAux[10] = '\0';
    timestampAux[10] = '\0';

    string userId = userIdAux; // Convertendo para string para facilitar a manipulação
    string productId = productIdAux;
    string timestampString = timestampAux;

    ProductReview *pr = new ProductReview(userId, productId, ratingAux, timestampString); // Criando o objeto ProductReview

    delete[] userIdAux;
    delete[] productIdAux;
    delete[] timestampAux;

    return pr;
}

ProductReview *ProductReview::import(int n)
{
    fstream arq("ratings_Electronics.bin", ios::in | ios::binary);

    if (!arq.is_open())
    {
        cout << "O arquivo binário ainda não foi criado!" << endl;
        return nullptr;
    }

    arq.seekg(0); // Posiciona o ponteiro no início do arquivo

    // Numero de Registros - 7824483

    random_device dev; // Gerador de numeros aleatorios
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(0, TOTAL_REGISTROS); // distribution in range [1,TOTALREGISTROS]

    ProductReview *vet = new ProductReview[n];

    for (int i = 0; i < n; i++)
    {
        int indiceAleatorio = dist(rng);
        ProductReview *pr = this->getProductReview(indiceAleatorio);

        vet[i] = *pr;
    }

    return vet;
}

void ProductReview::createBinary(string dirCsv)
{
    ifstream arqCsv(dirCsv + ".csv", ios::in);
    cout << dirCsv + ".csv" << endl;
    if (!arqCsv.is_open())
    {
        cout << "O arquivo csv não foi encontrado!" << endl;
        exit(1);
    }

    ofstream arqBin(dirCsv + ".bin", ios::out | ios::app | ios::binary);

    string user_idAux;
    string product_idAux;
    string ratingAux;
    string timestampAux;

    while (!arqCsv.eof())
    {
        getline(arqCsv, user_idAux, ','); // Pegando os dados do arquivo csv, separados por vírgula
        getline(arqCsv, product_idAux, ',');
        getline(arqCsv, ratingAux, ',');
        getline(arqCsv, timestampAux, '\n'); // O último dado não é separado por vírgula

        float ratingFloat = stof(ratingAux); // Convertendo o rating para float

        if (arqBin.is_open())
        {
            arqBin.write(reinterpret_cast<const char *>(user_idAux.c_str()), 21); // O maior id de usuário encontrado tem 21 caracteres
            arqBin.write(reinterpret_cast<const char *>(product_idAux.c_str()), 10);
            arqBin.write(reinterpret_cast<const char *>(&ratingFloat), sizeof(float));
            arqBin.write(reinterpret_cast<const char *>(timestampAux.c_str()), 10); // Existem timestamps de 9 caracteres, salvando com 10 para facilitar a leitura
        }
        else
        {
            cout << "ERRO: O arquivo nao pode ser aberto!" << endl;
        }
    }

    arqCsv.close();
}

void ProductReview::getReview(int indice)
{
    // imprime o ProductReview
    ProductReview *pr = this->getProductReview(indice);
    pr->print();
}

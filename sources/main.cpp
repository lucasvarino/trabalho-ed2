#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>
#include "../headers/ProductReview.h"
#include "../headers/Sort.h"
#include "../headers/Hash.h"

#define FILE_NAME "ratings_Electronics"
#define TOTAL_REGISTROS 7824483
#define MIN 0

using namespace std;
using namespace std::chrono;

// Fisher-Yates Shuffle
int *shuffle(int *vetor, int tamanho)
{
    int i, j;
    int aux;

    unsigned seed = system_clock::now().time_since_epoch().count();
    srand(seed);

    for (int i = 0; i < TOTAL_REGISTROS; i++)
    {
        vetor[i] = i;
    }

    for (i = TOTAL_REGISTROS - MIN - 1; i > 0; i--)
    {
        j = rand() % (i + 1);
        aux = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = aux;
    }

    int *vetorAleatorio = new int[tamanho];

    for (int i = 0; i < tamanho; i++)
    {
        vetorAleatorio[i] = vetor[i];
    }

    delete[] vetor;

    return vetorAleatorio;
}

RegistroHash *createTable(int n)
{
    int *indices = new int[TOTAL_REGISTROS];
    int *aleatorios = shuffle(indices, n);
    ProductReview aux;

    ProductReview *vet = new ProductReview[n];
    Hash *hash = new Hash(n);

    for (int i = 0; i < n; i++)
    {
        vet[i] = *aux.getReview(aleatorios[i]);
        RegistroHash *registro = new RegistroHash;
        registro->productId = vet[i].getProductId();
        registro->qtdReviews = 1;
        hash->insert(vet[i].getProductId(), registro);
    }

    return hash->getVetor();
}

void createBinary(string &path)
{
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    string dirBin = path + FILE_NAME + ".bin";
    string dirCsv = path + FILE_NAME;

    ifstream arqBin(dirBin, ios::in);

    if (arqBin.is_open())
    {
        cout << "O arquivo binário já foi criado." << endl;
        return;
    }
    cout << "Criando arquivo binário..." << endl;
    ProductReview::createBinary(dirCsv);
    high_resolution_clock::time_point fim = high_resolution_clock::now();

    cout << "Arquivo binário criado." << endl
         << "Tempo gasto para a criação: " << duration_cast<duration<double>>(fim - inicio).count() << " segundos" << endl;
}

Sort *sort(ProductReview *vet, int n, int methodId)
{
    Sort *sort = new Sort();
    switch (methodId)
    {
    case 0:
        sort->quickSort(vet, 0, n - 1);
        break;
    case 1:
        sort->mergeSort(vet, 0, n - 1, 0);
        break;
    case 2:
        sort->timSort(vet, n);
        break;
    default:
        break;
    }
    return sort;
}

void gerarMetricas(int methodId)
{
    ifstream arq2("input.dat", ios::in | ios::binary);

    vector<int> tamConjuntos;

    if (!arq2.is_open())
    {
        cout << "Arquivo de Input .dat não encontrado." << endl;
        cout << "Gerando um Input com os valores padrão especificados no documento..." << endl;
        ofstream arq("input.dat", ios::out | ios::binary | ios::app);

        tamConjuntos.push_back(10000);
        tamConjuntos.push_back(50000);
        tamConjuntos.push_back(100000);
        tamConjuntos.push_back(500000);
        tamConjuntos.push_back(1000000);

        for (int i = 0; i < 5; i++)
        {
            arq.write(reinterpret_cast<char *>(&tamConjuntos.at(i)), sizeof(int));
        }
    }
    else
    {
        cout << "Arquivo de Input .dat encontrado." << endl;
        cout << "Lendo valores do arquivo..." << endl;

        while (!arq2.eof())
        {
            int tam;
            arq2.read(reinterpret_cast<char *>(&tam), sizeof(int));
            tamConjuntos.push_back(tam);
        }
    }

    int qtdConjuntos = 3;
    ProductReview pr;

    int mediaComparacoes = 0;
    int mediaTrocas = 0;
    double mediaTempo = 0;

    ofstream arqTxt("output.txt", ios::out | ios::app);
    arqTxt << "---------------------" << endl;
    arqTxt << "Método " << methodId << endl;
    arqTxt << "---------------------" << endl;
    arqTxt << endl
           << endl;

    for (int i = 0; i < tamConjuntos.size(); i++)
    {
        for (int j = 0; j < qtdConjuntos; j++)
        {
            high_resolution_clock::time_point inicio = high_resolution_clock::now();

            ProductReview *conjunto = pr.import(tamConjuntos.at(i));
            Sort *metricas = sort(conjunto, tamConjuntos.at(i), methodId);

            high_resolution_clock::time_point fim = high_resolution_clock::now();
            metricas->setTempo(duration_cast<duration<double>>(fim - inicio).count());

            mediaComparacoes += metricas->getComparacoes();
            mediaTrocas += metricas->getTrocas();
            mediaTempo += metricas->getTempo();

            arqTxt << "Conjunto de Tamanho: " << tamConjuntos.at(i) << endl;
            arqTxt << "Comparacoes: " << metricas->getComparacoes() << endl;
            arqTxt << "Trocas: " << metricas->getTrocas() << endl;
            arqTxt << "Tempo: " << metricas->getTempo() << endl;
            arqTxt << endl;

            delete[] conjunto;
            delete metricas;
        }

        arqTxt << endl;
        arqTxt << "Media de Comparacoes: " << mediaComparacoes / qtdConjuntos << endl;
        arqTxt << "Media de Trocas: " << mediaTrocas / qtdConjuntos << endl;
        arqTxt << "Media de Tempo: " << mediaTempo / qtdConjuntos << endl;
        arqTxt << "---------------------------------" << endl;

        mediaComparacoes = 0;
        mediaTrocas = 0;
        mediaTempo = 0;
    }
}

void printMenu()
{
    cout << "Menu de opções" << endl;
    cout << "Escolha sua opção" << endl;
    cout << "1 Ordenação" << endl;
    cout << "2 Hash" << endl;
    int opcao;
    cin >> opcao;
    switch (opcao)
    {
    case 1:
    {
        cout << "Seleciona o método" << endl
             << "0 - Quick Sort" << endl
             << "1 - Merge Sort" << endl
             << "2 - Tim Sort" << endl;
        int metodo;
        cin >> metodo;
        gerarMetricas(metodo);
        printMenu();
        break;
    }
    case 2:
    {
        cout << "Insira o tamanho da tabela hash" << endl;
        int tamanho;
        cin >> tamanho;
        RegistroHash *vet = createTable(tamanho);
        Hash::quickSortHash(vet, 0, tamanho - 1);
        cout << "Insira a quantidade produtos que deseja ver" << endl;
        int qtd;
        cin >> qtd;
        for (int i = 0; i < qtd; i++)
        {
            cout << "Produto: " << vet[i].productId << " Quantidade de reviews: " << vet[i].qtdReviews << endl;
        }
        printMenu();
        break;
    }
    default:
    {
        cout << "Saindo do Programa..." << endl;
        return;
    }
    }
}

int main(int argc, char const *argv[])
{

    if (argc <= 1)
    {
        cout << "ERRO: Caminho não informado." << endl;
        return 0;
    }

    string path = argv[1];

    createBinary(path);
    printMenu();
}

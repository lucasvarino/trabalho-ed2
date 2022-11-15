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
    srand(seed); //Criação da Seed para a geracao de numeros aleatorios

    for (int i = 0; i < TOTAL_REGISTROS; i++)
    {
        vetor[i] = i; //Alocando os valores de 0 a total de registros no vetor
    }

    for (i = TOTAL_REGISTROS - MIN - 1; i > 0; i--)
    {
        j = rand() % (i + 1); //Gerando o índice aleatório
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
    int *indices = new int[TOTAL_REGISTROS]; //Vetor com os indices de 0 a total de registros
    int *aleatorios = shuffle(indices, n); // Geração do vetor com n indices aleatórios
    ProductReview aux;

    ProductReview *vet = new ProductReview[n];
    Hash *hash = new Hash(n); //Criação da tabela hash

    for (int i = 0; i < n; i++)
    {
        vet[i] = *aux.getProductReview(aleatorios[i]); //Alocando os registros aleatórios no vetor
        RegistroHash *registro = new RegistroHash; //Criação do registro
        registro->productId = vet[i].getProductId(); //Atribuição do productId
        registro->qtdReviews = 1; //Atribuição da quantidade de reviews
        hash->insert(vet[i].getProductId(), registro); //Inserção do registro na tabela hash
    }

    return hash->getVetor(); //Retorna o vetor da tabela hash
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
    ProductReview::createBinary(dirCsv); //Função estática que cria o arquivo binário
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
    return sort; //Retornamos Sort para ter acesso às métricas
}

void gerarMetricas(int methodId)
{
    ifstream arq2("input.dat", ios::in | ios::binary);

    vector<int> tamConjuntos; //Vetor com os tamanhos dos conjuntos (passados pelo .dat ou por padrão)

    if (!arq2.is_open())
    {
        cout << "Arquivo de Input .dat não encontrado." << endl;
        cout << "Gerando um Input com os valores padrão especificados no documento..." << endl;
        ofstream arq("input.dat", ios::out | ios::binary | ios::app);

        //Caso não tenha um .dat, inserimos os valores que estão na especificação do trabalho
        tamConjuntos.push_back(10000);
        tamConjuntos.push_back(50000);
        tamConjuntos.push_back(100000);
        tamConjuntos.push_back(500000);
        tamConjuntos.push_back(1000000);

        for (int i = 0; i < 5; i++)
        {
            arq.write(reinterpret_cast<char *>(&tamConjuntos.at(i)), sizeof(int)); //Escrevendo no arquivo .dat
        }
    }
    else
    {
        cout << "Arquivo de Input .dat encontrado." << endl;
        cout << "Lendo valores do arquivo..." << endl;

        while (!arq2.eof())
        {
            int tam;
            arq2.read(reinterpret_cast<char *>(&tam), sizeof(int)); //Lendo os valores do arquivo .dat
            tamConjuntos.push_back(tam); //Inserindo os valores no vetor
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

            ProductReview *conjunto = pr.import(tamConjuntos.at(i)); //Importando o conjunto de registros a ser ordenado
            Sort *metricas = sort(conjunto, tamConjuntos.at(i), methodId); //Ordenando o conjunto

            high_resolution_clock::time_point fim = high_resolution_clock::now();
            metricas->setTempo(duration_cast<duration<double>>(fim - inicio).count()); //Atribuindo o tempo de execução

            mediaComparacoes += metricas->getComparacoes(); //Somando as comparações
            mediaTrocas += metricas->getTrocas(); //Somando as trocas
            mediaTempo += metricas->getTempo(); //Somando o tempo

            arqTxt << "Conjunto de Tamanho: " << tamConjuntos.at(i) << endl;
            arqTxt << "Comparacoes: " << metricas->getComparacoes() << endl;
            arqTxt << "Trocas: " << metricas->getTrocas() << endl;
            arqTxt << "Tempo: " << metricas->getTempo() << endl;
            arqTxt << endl; //Escrita das métricas no output.txt

            delete[] conjunto;
            delete metricas;
        }
        //Escrita das médias das métricas no .txt
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

void printMenu() //Menu de execução
{
    cout << "Menu de opções" << endl;
    cout << "Escolha sua opção" << endl;
    cout << "1 Ordenação" << endl;
    cout << "2 Hash" << endl;
    cout << "3 Sair" << endl;
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
        Hash::quickSortHash(vet, 0, tamanho - 1); //Ordenando o vetor de registros
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

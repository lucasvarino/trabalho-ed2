#ifndef ARVOREB_INCLUDED
#define ARVOREB_INCLUDED
// TAD Arvore B
#include "../headers/NoB.h"
#include "../headers/ProductReview.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ArvoreB
{
private:
    int ordem;
    NoB *raiz;
    string binLocation;
    string id;

public:
    ArvoreB(int ordem);
    ~ArvoreB();

    void insere(ProductReview *pr);
    ProductReview *busca(string userId, string productId);
    void print();
    
};

#endif // ARVOREB_INCLUDED
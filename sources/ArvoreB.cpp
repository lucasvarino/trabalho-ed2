#include "../headers/ArvoreB.h"
#include "../headers/NoB.h"
#include "../headers/ProductReview.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ArvoreB::ArvoreB(int ordem)
{
    this->ordem = ordem;
    this->raiz = new NoB(ordem);
    this->binLocation = "";
    this->id = "";
}

ArvoreB::~ArvoreB()
{
    delete this->raiz;
}

void ArvoreB::insere(ProductReview *pr)
{
    NoB *noAtual = this->raiz;
    string chave = pr->getUserId() + pr->getProductId();
    int i = noAtual->getNChaves() - 1;

  
}
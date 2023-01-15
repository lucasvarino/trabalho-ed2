#include "../headers/ArvoreB.h"
#include "../headers/ProductReview.h"
#include "../headers/NoB.h"
#include <chrono>

#include <iostream>

using namespace std;
using namespace std::chrono;

ArvoreB::ArvoreB(int t){
    root = NULL;
    this->t = t;
    comparacoes = 0;
}
ArvoreB::~ArvoreB(){
    delete root;
}
ProductReview* ArvoreB::busca(string userID, string productID){
    
    string chave = userID+productID;
    if (root == NULL){
        cout<< "Arvore vazia" << endl;
        return NULL;
    }else{
        int *pos = new int;
        NoB *aux =  root->search(chave, *pos);
        ProductReview *pr = aux->getKey(*pos);
        return pr;

    }
}
void ArvoreB::insere(ProductReview *pr)
{
    string chave = pr->getUserId()+pr->getProductId();
    if (root == NULL)
    {
        int comparacoes = 0;
        root = new NoB(t, true);
        root->setKey(0,*pr);  
        root->setId(0,pr);  
        root->setN(1); 
    }
    else
    {
        if (root->getN() == 2*root->getT()-1)
        {
            NoB* NoAux = new NoB(t, false);
            NoAux->setC(0,root);
            NoAux->split(0, root);
            int i = 0;
            comparacoes++;
            if (NoAux->getId(0)< chave){
                i++;
            }
            NoAux->getC(i)->insertion(chave, *pr, comparacoes);
            root = NoAux;
        }
        else { 
            root->insertion(chave, *pr, comparacoes);
        }
    }
    setComparacoes(comparacoes);
}
void ArvoreB::passseio()
{
    if (root != NULL) root->traverse();
}
void ArvoreB::print(){
    if (root != NULL) root->print();
}
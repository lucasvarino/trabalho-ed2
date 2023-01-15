#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED


#include "../headers/NoB.h"
#include "../headers/ProductReview.h"
#include <iostream>

using namespace std;

class ArvoreB{
    private:
        NoB *root;
        int t;
        int comparacoes;

    public:
        ArvoreB(int _t);
        void print();
        void insere(ProductReview *pr);
        ProductReview* busca(string userID, string productID);
        void passseio();
        int getComparacoes(){return comparacoes;};
        void setComparacoes(int _comparacoes){comparacoes = _comparacoes;};
};

#endif // ARVOREB_H_INCLUDED
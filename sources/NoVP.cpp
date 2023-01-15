#include "../headers/NoVP.h"
#include <iostream>

using namespace std;

NoVP::NoVP(int data){
    this->data = data;
    this->esq = NULL;
    this->dir = NULL;
    this->cor = 'R';
    this->parente = NULL;
}

NoVP::~NoVP(){
    delete this->esq;
    delete this->dir;
}

NoVP NoVP::rodaEsq(NoVP *no){
    NoVP *x  = no->dir;
    NoVP *y = x->esq;
    x->esq = no;
    no->dir = y;
    no->parente = x;
    if(y != NULL){
        y->parente = no;
    }
    return *x;
}

NoVP NoVP::rodaDir(NoVP *no){
    NoVP *x = no->esq;
    NoVP *y = x->dir;
    x->dir = no;
}
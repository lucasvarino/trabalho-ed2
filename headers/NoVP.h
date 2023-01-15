#ifndef NOVP_H_INCLUDED
#define NOVP_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class NoVP{
    private:
    int data;
    NoVP *esq;
    NoVP *dir;
    char cor;
    NoVP *parente;

    public:
    NoVP(int data);
    ~NoVP();
    NoVP rodaEsq(NoVP *no);
    NoVP rodaDir(NoVP *no);
};







#endif // NOVP_H_INCLUDED
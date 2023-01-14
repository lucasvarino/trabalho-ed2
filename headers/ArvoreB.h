#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED


#include "../headers/NoB.h"
#include <iostream>

using namespace std;

class ArvoreB{
    private:
        NoB *root;
        int t;
    public:
        ArvoreB(int _t);
        void print();
        void insert(int k);
        NoB* search(int k);
        void traverse();

};

#endif // ARVOREB_H_INCLUDED
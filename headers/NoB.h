#ifndef NOB_H_INCLUDED
#define NOB_H_INCLUDED

#include <iostream>
#include "../headers/ProductReview.h"

using namespace std;

class NoB
{
    private:
    ProductReview *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    NoB **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
    string *id;
        
    public:
    NoB(int _t, bool _leaf);   
    void insertion(string k, ProductReview pr, int &comparacoes);
    void split(int i, NoB *y);
    void traverse();
    NoB *search(string chave, int &pos);
    int getN(){return n;};
    void setN(int _n){n = _n;};
    ProductReview *getKey(int i){return &keys[i];};
    void setKey(int i, ProductReview k);
    int getT(){return t;};
    void setT(int _t){t = _t;};
    NoB* getC(int i){return C[i];};
    void setC(int i, NoB* _C){C[i] = _C;};
    string getId(int i){return id[i];};
    void setId(int i, ProductReview *pr);
    void print();
};






#endif // NOB_H_INCLUDED
#ifndef NOB_H_INCLUDED
#define NOB_H_INCLUDED

#include <iostream>

using namespace std;

class NoB
{
    private:
    int *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    NoB **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
        
    public:
    NoB(int _t, bool _leaf);   
    void insertNonFull(int k);
    void splitChild(int i, NoB *y);
    void traverse();
    NoB *search(int k);
    int getN(){return n;};
    void setN(int _n){n = _n;};
    int getKey(int i){return keys[i];};
    void setKey(int i, int k){keys[i] = k;};
    int getT(){return t;};
    void setT(int _t){t = _t;};
    NoB* getC(int i){return C[i];};
    void setC(int i, NoB* _C){C[i] = _C;};
};






#endif // NOB_H_INCLUDED
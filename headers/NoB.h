#ifndef NOB_INCLUDED
#define NOB_INCLUDED

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class NoB
{
private:
    int *chaves;
    int nChaves;
    NoB **filhos;
    int nFilhos;
    bool folha;
    NoB *pai;
    string binLocation;
    string id;



public:
    NoB(int ordem);
    ~NoB();

    int getNChaves() { return this->nChaves; };
    int getNFilhos() { return this->nFilhos; };
    bool getFolha() { return this->folha; };
    NoB *getPai() { return this->pai; };
    int *getChaves() { return this->chaves; };
    NoB **getFilhos() { return this->filhos; };
    string getBinLocation() { return this->binLocation; };
    string getId() { return this->id; };

    void setNChaves(int nChaves) { this->nChaves = nChaves; };
    void setNFilhos(int nFilhos) { this->nFilhos = nFilhos; };
    void setFolha(bool folha) { this->folha = folha; };
    void setPai(NoB *pai) { this->pai = pai; };
    void setChaves(int *chaves) { this->chaves = chaves; };
    void setFilhos(NoB **filhos) { this->filhos = filhos; };
    void setBinLocation(string binLocation) { this->binLocation = binLocation; };
    void setId(string id) { this->id = id; };

    void print();
    void printChaves();
    void printFilhos();
    void printPai();
    void printFolha();
    void printNChaves();
    void printNFilhos();
    void printNo();
};

#endif // NOB_INCLUDED
#include "../headers/NoB.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

NoB::NoB(int ordem)
{
    this->chaves = new int[ordem - 1];
    this->filhos = new NoB *[ordem];
    this->nChaves = 0;
    this->nFilhos = 0;
    this->folha = true;
    this->pai = NULL;
    this->binLocation = "";
    this->id = "";
}

NoB::~NoB()
{
    delete[] this->chaves;
    delete[] this->filhos;
}

void NoB::setBinLocation(string binLocation)
{
    this->binLocation = binLocation;
}
void NoB::setId(string id)
{
    this->id = id;
}



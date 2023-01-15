#ifndef NOVP_H_INCLUDED
#define NOVP_H_INCLUDED

#include <iostream>
#include <string>
#include "../headers/ProductReview.h"

using namespace std;

class NoVP
{
private:
public:
    bool color; // true = red, false = black
    string data;
    NoVP *left;
    NoVP *right;
    NoVP *parent;
    ProductReview *pr;


public:
    NoVP(string data, ProductReview *pr);
    ~NoVP();
    NoVP *grandparent();
    NoVP *uncle();
    void rotateLeft();
    void rotateRight();
};

#endif // NOVP_H_INCLUDED
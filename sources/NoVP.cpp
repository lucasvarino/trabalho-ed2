#include "../headers/NoVP.h"
#include <iostream>
#include "../headers/ProductReview.h"

using namespace std;

NoVP::NoVP(string data, ProductReview *pr)
{
    this->data = data;
    this->color = true;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->pr = pr;
}

NoVP::~NoVP()
{
    // dtor
}

NoVP *NoVP::grandparent()
{
    if (this->parent == nullptr)
        return nullptr;
    return this->parent->parent;
}

NoVP *NoVP::uncle()
{
    NoVP *g = this->grandparent();
    if (g == nullptr)
        return nullptr;
    if (this->parent == g->left)
        return g->right;
    else
        return g->left;
}

void NoVP::rotateLeft()
{
    NoVP *p = this->right;
    this->right = p->left;
    p->left->parent = this;
    p->parent = this->parent;
    if (this->parent != nullptr)
    {
        if (this == this->parent->left)
            this->parent->left = p;
        else
            this->parent->right = p;
    }
    p->left = this;
    this->parent = p;
}

void NoVP::rotateRight()
{
    NoVP *p = this->left;
    this->left = p->right;
    p->right->parent = this;
    p->parent = this->parent;
    if (this->parent != nullptr)
    {
        if (this == this->parent->left)
            this->parent->left = p;
        else
            this->parent->right = p;
    }
    p->right = this;
    this->parent = p;
}

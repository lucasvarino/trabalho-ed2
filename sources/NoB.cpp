#include "../headers/NoB.h"
#include "../headers/ProductReview.h"

#include <iostream>

using namespace std;

NoB::NoB(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;
    keys = new ProductReview[2 * t - 1];
    C = new NoB *[2 * t];
    id = new string[2 * t - 1];
    n = 0;
}

void NoB::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse();
    }
    if (leaf == false)
        C[i]->traverse();
}

NoB *NoB::search(string chave, int &pos)
{
    int i = 0;
    while (i < n && chave > id[i])
        i++;

    if (chave == id[i])
        return this;

    if (leaf == true)
        return NULL;

    return C[i]->search(chave, pos);
}
void NoB::insertion(string chave, ProductReview pr, int &comparacoes)
{

    int i = n - 1;

    if (leaf == true)
    {
        while (i >= 0 && id[i] > chave)
        {
            comparacoes++;
            keys[i + 1] = keys[i];
            id[i + 1] = id[i];
            i--;
        }
        keys[i + 1] = pr;
        id[i + 1] = chave;
        n = n + 1;
    }
    else
    {

        while (i >= 0 && id[i] > chave)
        {
            comparacoes++;
            i--;
        }

        if (C[i + 1]->n == 2 * t - 1)
        {

            split(i + 1, C[i + 1]);
            comparacoes++;
            if (id[i + 1] < chave)
            {
                i++;
            }
        }
        C[i + 1]->insertion(chave, pr, comparacoes);
    }
}
void NoB::split(int i, NoB *y)
{
    NoB *z = new NoB(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
    {
        z->keys[j] = y->keys[j + t];
        z->id[j] = y->id[j + t];
    }

    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
    {
        keys[j + 1] = keys[j];
        id[j + 1] = id[j];
    }

    keys[i] = y->keys[t - 1];
    id[i] = y->id[t - 1];

    n = n + 1;
}
void NoB::setKey(int pos, ProductReview pr)
{
    keys[pos] = pr;
    setId(pos, &pr);
}
void NoB::setId(int pos, ProductReview *pr)
{
    id[pos] = pr->getUserId() + pr->getProductId();
}
void NoB::print()
{

    int i;
    for (i = 0; i < n; i++)
    {

        if (leaf == false)
            C[i]->print();
        cout << " " << id[i];
    }

    if (leaf == false)
        C[i]->print();
}
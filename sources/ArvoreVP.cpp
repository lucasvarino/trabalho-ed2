#include "../headers/ArvoreVP.h"
#include <iostream>
#include "../headers/ProductReview.h"

using namespace std;

ArvoreVP::ArvoreVP()
{
    this->root = nullptr;
    this->comparacoes = 0;
}

ArvoreVP::~ArvoreVP()
{
    // dtor
}

void ArvoreVP::insere(ProductReview *data)
{
    string chave = data->getUserId() + data->getProductId();
    if (root == nullptr)
    {
        root = new NoVP(chave, data);
        root->color = false;
    }
    else
    {
        insert(root, data);
    }
}

void ArvoreVP::insert(NoVP *n, ProductReview *data)
{
    string chave = data->getUserId() + data->getProductId();
    comparacoes++;
    if (chave < n->data)
    {
        if (n->left == nullptr)
        {
            n->left = new NoVP(chave, data);
            n->left->parent = n;
            fixInsert(n->left);
        }
        else
        {
            insert(n->left, data);
        }
    }
    else
    {
        if (n->right == nullptr)
        {
            n->right = new NoVP(chave, data);
            n->right->parent = n;
            fixInsert(n->right);
        }
        else
        {
            insert(n->right, data);
        }
    }
}
void ArvoreVP::fixInsert(NoVP *n)
{
    while (n->parent != nullptr && n->parent->color)
    {
        NoVP *uncle = nullptr;
        NoVP *grandparent = n->parent->parent;
        comparacoes++;
        if (n->parent == grandparent->left)
        {
            uncle = grandparent->right;
            if (uncle != nullptr && uncle->color)
            {
                n->parent->color = false;
                uncle->color = false;
                grandparent->color = true;
                n = grandparent;
            }
            else
            {
                comparacoes++;
                if (n == n->parent->right)
                {
                    n = n->parent;
                    rotateLeft(n);
                }
                n->parent->color = false;
                grandparent->color = true;
                rotateRight(grandparent);
            }
        }
        else
        {
            uncle = grandparent->left;
            if (uncle != nullptr && uncle->color)
            {
                n->parent->color = false;
                uncle->color = false;
                grandparent->color = true;
                n = grandparent;
            }
            else
            {
                comparacoes++;
                if (n == n->parent->left)
                {
                    n = n->parent;
                    rotateRight(n);
                }
                n->parent->color = false;
                grandparent->color = true;
                rotateLeft(grandparent);
            }
        }
    }
    root->color = false;
}
void ArvoreVP::rotateRight(NoVP *n)
{
    NoVP *p = n->left;
    n->left = p->right;
    if (p->right != nullptr)
    {
        p->right->parent = n;
    }
    p->parent = n->parent;
    if (n->parent == nullptr)
    {
        root = p;
    }
    else if (n == n->parent->left)
    {
        comparacoes++;
        n->parent->left = p;
    }
    else
    {   
        comparacoes++;
        n->parent->right = p;
    }
    p->right = n;
    n->parent = p;
}
void ArvoreVP::rotateLeft(NoVP *n)
{
    NoVP *p = n->right;
    n->right = p->left;
    if (p->left != nullptr)
    {
        p->left->parent = n;
    }
    p->parent = n->parent;
    if (n->parent == nullptr)
    {
        root = p;
    }
    else if (n == n->parent->left)
    {
        comparacoes++;
        n->parent->left = p;
    }
    else
    {
        comparacoes++;
        n->parent->right = p;
    }
    p->left = n;
    n->parent = p;
}
ProductReview *ArvoreVP::busca(string userID, string ProductID)
{
    NoVP *current = root;
    string data = userID + ProductID;
    while (current != nullptr)
    {
        comparacoes++;
        if (data == current->data)
        {
            return current->pr;
        }
        else if (data < current->data)
        {
            comparacoes++;
            current = current->left;
        }
        else
        {
            comparacoes++;
            current = current->right;
        }
    }
    return nullptr;
}

void ArvoreVP::print()
{
    printInOrder(root);
}

void ArvoreVP::printInOrder(NoVP *node) {
    if (node != nullptr) {
        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }
}
int ArvoreVP::getComparacoes()
{
    return comparacoes;
}

void ArvoreVP::setComparacoes(int comparacoes)
{
    this->comparacoes = comparacoes;
}
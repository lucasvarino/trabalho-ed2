#include "../headers/ArvoreVP.h"
#include <iostream>
#include "../headers/ProductReview.h"

using namespace std;

ArvoreVP::ArvoreVP()
{
    this->root = nullptr;
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
    if (chave < n->data)
    {
        cout << "A" << endl;
        if (n->left == nullptr)
        {
            cout << "B" << endl;
            n->left = new NoVP(chave, data);
            n->left->parent = n;
            fixInsert(n->left);
        }
        else
        {
            cout << "C" << endl;
            insert(n->left, data);
        }
    }
    else
    {
        if (n->right == nullptr)
        {
            cout << "D" << endl;
            n->right = new NoVP(chave, data);
            n->right->parent = n;
            fixInsert(n->right);
        }
        else
        {
            cout << "E" << endl;
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
        n->parent->left = p;
    }
    else
    {
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
        n->parent->left = p;
    }
    else
    {
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
        if (data == current->data)
        {
            return current->pr;
        }
        else if (data < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return nullptr;
}

void ArvoreVP::print()
{
    print(root, 0);
}

void ArvoreVP::print(NoVP *n, int level)
{
    if (n == nullptr)
    {
        return;
    }
    print(n->right, level + 1);
    for (int i = 0; i < level; i++)
    {
        cout << "    ";
    }
    std::cout << n->data << "(" << (n->color ? "red" : "black") << ")" << endl;
    print(n->left, level + 1);
}
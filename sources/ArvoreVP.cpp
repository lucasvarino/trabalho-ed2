#include "../headers/ArvoreVP.h"
#include <iostream>

using namespace std;

ArvoreVP::ArvoreVP()
{
    this->root = NULL;
}

NoVP *ArvoreVP::rotateLeft(NoVP *noVP)
{
    NoVP *aux = noVP->getRight();
    noVP->setRight(aux->getLeft());
    if (aux->getLeft() != NULL)
    {
        aux->getLeft()->setParent(noVP);
    }
    aux->setParent(noVP->getParent());
    if (noVP->getParent() == NULL)
    {
        this->root = aux;
    }
    else if (noVP == noVP->getParent()->getLeft())
    {
        noVP->getParent()->setLeft(aux);
    }
    else
    {
        noVP->getParent()->setRight(aux);
    }
    aux->setLeft(noVP);
    noVP->setParent(aux);
    return aux;
}

NoVP *ArvoreVP::rotateRight(NoVP *noVP)
{
    NoVP *aux = noVP->getLeft();
    noVP->setLeft(aux->getRight());
    if (aux->getRight() != NULL)
    {
        aux->getRight()->setParent(noVP);
    }
    aux->setParent(noVP->getParent());
    if (noVP->getParent() == NULL)
    {
        this->root = aux;
    }
    else if (noVP == noVP->getParent()->getRight())
    {
        noVP->getParent()->setRight(aux);
    }
    else
    {
        noVP->getParent()->setLeft(aux);
    }
    aux->setRight(noVP);
    noVP->setParent(aux);
    return aux;
}

NoVP *ArvoreVP::insertHelp(NoVP *root, int data)
{

    bool f = false;
    bool ll = false;
    bool lr = false;
    bool rl = false;
    bool rr = false;

    if(root == NULL){
        root = new NoVP(data);
        root->setColor('B');
        return root;
    }
    else if(data < root->getData()){
        root->setLeft(insertHelp(root->getLeft(), data));
            root->getLeft()->setParent(root);
            if (root != this->root)
            {
                if (root->getColor() == 'R' && root->getLeft()->getColor() == 'R')
                    f = true;
            }
    }
    else
        {
            root->setRight(insertHelp(root->getRight(), data));
            root->getRight()->setParent(root);
            if (root != this->root)
            {
                if (root->getColor() == 'R' && root->getRight()->getColor() == 'R')
                    f = true;
            }
        
        }
         if (ll)
        {
            root = rotateLeft(root);
            root->setColor('B');
            root->getLeft()->setColor('R');
            ll = false;
        }
        else if (rr)
        {
            root = rotateRight(root);
            root->setColor('B');
            root-> getRight()->setColor('R');
            rr = false;
        }
        else if (lr)
        {
            root->setLeft(rotateLeft(root->getLeft()));
            root->getLeft()->setParent(root);
            root = rotateRight(root);
            root->setColor('B');
            root->getRight()->setColor('R');
            lr = false;
        }
        else if (rl)
        {
            root->setRight(rotateRight(root->getRight()));
            root->getRight()->setParent(root);
            root = rotateLeft(root);
            root->setColor('B');
            root->getLeft()->setColor('R');
            rl = false;
        }
 if (f)
    {
        if (root->getParent()->getRight()==root)  // to check which child is the current node of its parent
        {
            if (root->getParent()->getLeft()->getColor() == 'R')
            {
                root->getParent()->setColor('R');
                root->getParent()->getLeft()->setColor('B');
                root->getParent()->getRight()->setColor('B');
                if (root->getParent() != this->root)
                {
                    if (root->getParent()->getParent()->getColor() == 'R')
                    {
                        if (root->getParent()->getParent()->getLeft() == root->getParent())
                        {
                            ll = true;
                        }
                        else
                        {
                            rr = true;
                        }
                    }
                }
            }
            else
            {
                if (root->getParent()->getRight()->getLeft() == root)
                {
                    rl = true;
                }
                else
                {
                    rr = true;
                }
            }
        }
        else
        {
            if (root->getParent()->getRight()->getColor() == 'R')
            {
                root->getParent()->setColor('R');
                root->getParent()->getLeft()->setColor('B');
                root->getParent()->getRight()->setColor('B');
                if (root->getParent() != this->root)
                {
                    if (root->getParent()->getParent()->getColor() == 'R')
                    {
                        if (root->getParent()->getParent()->getLeft() == root->getParent())
                        {
                            ll = true;
                        }
                        else
                        {
                            rr = true;
                        }
                    }
                }
            }
            else
            {
                if (root->getParent()->getLeft()->getRight() == root)
                {
                    lr = true;
                }
                else
                {
                    ll = true;
                }
            }
        }
        f = false;
    }
    return root;
}
void ArvoreVP::insert(int data)
{
    if (this->root == NULL)
    {
        this->root = new NoVP(data);
        this->root->setColor('B');
        cout<<"Root"<<endl;
    }
    else
    {
        this->root = insertHelp(this->root, data);
    }
}
void ArvoreVP::inorderTraversalHelper(NoVP *root)
{
    if (root != NULL)
    {
        inorderTraversalHelper(root->getLeft());
        cout << root->getData() << " ";
        inorderTraversalHelper(root->getRight());
    }
}
void ArvoreVP::inorderTraversal()
{
    inorderTraversalHelper(this->root);
    cout << endl;
}
void ArvoreVP::printTreeHelper(NoVP *root, int space)
{
    if (root == NULL)
        return;
    space += 10;
    printTreeHelper(root->getRight(), space);
    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    cout << root->getData() << endl;
    printTreeHelper(root->getLeft(), space);
}
void ArvoreVP::printTree()
{
    printTreeHelper(this->root, 0);
}
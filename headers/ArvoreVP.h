#ifndef ARVOREVP_H_INCLUDED
#define ARVOREVP_H_INCLUDED

#include <iostream>
#include "NoVP.h"

using namespace std;

class ArvoreVP
{
private:
    NoVP *root;

public:
    ArvoreVP();
    NoVP *rotateLeft(NoVP *noVP);
    NoVP *rotateRight(NoVP *NoVP);
    NoVP *insertHelp(NoVP *root, int data);
    void insert(int data);
    // helper function to print inorder traversal
    void inorderTraversalHelper(NoVP *NoVP);
    // function to print inorder traversal
    void inorderTraversal();
    void printTreeHelper(NoVP *root, int space);
    void printTree();
};

#endif // ARVOREVP_H_INCLUDED
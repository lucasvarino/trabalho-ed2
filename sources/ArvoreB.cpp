#include "../headers/ArvoreB.h"

#include <iostream>

using namespace std;

ArvoreB::ArvoreB(int t){
    root = NULL;
    this->t = t;
}
NoB* ArvoreB::search(int k){
    if (root == NULL){
        cout<< "Arvore vazia" << endl;
        return NULL;
    }else{
        return  root->search(k);
    }
}
void ArvoreB::insert(int k)
{
    // If tree is empty
    if (root == NULL)
    {
        // Allocate memory for root
        root = new NoB(t, true);
        root->setKey(0,k);  // Insert key
        root->setN(1);  // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->getN() == 2*root->getT()-1)
        {
            // Allocate memory for new root
            NoB* NosB = new NoB(t, false);
 
            // Make old root as child of new root
            NosB->setC(0,root);
 
            // Split the old root and move 1 key to the new root
            NosB->splitChild(0, root);
 
            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (NosB->getKey(0)< k)
                i++;
            NosB->getC(i)->insertNonFull(k);
 
            // Change root
            root = NosB;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
    
}
void ArvoreB::traverse()
{
    if (root != NULL) root->traverse();
}
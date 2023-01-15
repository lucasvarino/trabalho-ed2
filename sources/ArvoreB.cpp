#include "../headers/ArvoreB.h"
#include "../headers/ProductReview.h"
#include "../headers/NoB.h"

#include <iostream>

using namespace std;

ArvoreB::ArvoreB(int t){
    root = NULL;
    this->t = t;
}
ProductReview* ArvoreB::busca(string userID, string productID){
    string chave = userID+productID;
    if (root == NULL){
        cout<< "Arvore vazia" << endl;
        return NULL;
    }else{
        int *pos = new int;
        NoB *aux =  root->search(chave, *pos);
        ProductReview *pr = aux->getKey(*pos);
        return pr;

    }
}
void ArvoreB::insere(ProductReview *pr)
{
    string chave = pr->getUserId()+pr->getProductId();
    if (root == NULL)
    {
        // Allocate memory for root
        root = new NoB(t, true);
        root->setKey(0,*pr);  // Insert key
        root->setId(0,pr);  // Insert Id
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
            if (NosB->getId(0)< chave)
                i++;
            NosB->getC(i)->insertNonFull(chave, *pr);
 
            // Change root
            root = NosB;
        }
        else { // If root is not full, call insertNonFull for root
            root->insertNonFull(chave, *pr);
        }
    }
    
}
void ArvoreB::traverse()
{
    if (root != NULL) root->traverse();
}
void ArvoreB::print(){
    if (root != NULL) root->print();
}
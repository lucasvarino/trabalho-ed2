#include "../headers/NoB.h"
#include "../headers/ProductReview.h"

#include <iostream>

using namespace std;

NoB::NoB(int t1, bool leaf1)
{
    // Copy the given minimum degree and leaf property
    t = t1;
    leaf = leaf1;
 
    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new ProductReview[2*t-1];
    C = new NoB *[2*t];
    id = new string[2*t-1];
 
    // Initialize the number of keys as 0
    n = 0;
}
 
// Function to traverse all nodes in a subtree rooted with this node
void NoB::traverse()
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse();
    }
 
    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}
 
// Function to search key k in subtree rooted with this node
NoB *NoB::search(string chave, int &pos)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && chave > id[i])
        i++;
 
    // If the found key is equal to k, return this node
    if (chave == id[i])
        return this;
 
    // If key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;
 
    // Go to the appropriate child
    return C[i]->search(chave, pos);
}
void NoB::insertNonFull(string chave, ProductReview pr)
{
    // Initialize index as index of rightmost element
    int i = n-1;
 
    // If this is a leaf node
    if (leaf == true)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && id[i] > chave)
        {
            keys[i+1] = keys[i];
            id[i+1] = id[i];
            i--;
        }
 
        // Insert the new key at found location
        keys[i+1] = pr;
        id[i+1] = chave;
        n = n+1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && id[i] > chave){
            i--;
        }
            
 
        // See if the found child is full
        if (C[i+1]->n == 2*t-1)
        {
            // If the child is full, then split it
            splitChild(i+1, C[i+1]);
            if (id[i+1] < chave){
                i++;
            }
        }
        C[i+1]->insertNonFull(chave, pr);
    }
}
void NoB::splitChild(int i, NoB *y)
{
    // Create a new node which is going to store (t-1) keys
    // of y
    NoB *z = new NoB(y->t, y->leaf);
    z->n = t - 1;
 
    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t-1; j++){
        z->keys[j] = y->keys[j+t];
        z->id[j] = y->id[j+t];
    }
 
    // Copy the last t children of y to z
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
 
    // Reduce the number of keys in y
    y->n = t - 1;
 
    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
 
    // Link the new child to this node
    C[i+1] = z;
 
    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    for (int j = n-1; j >= i; j--){
        keys[j+1] = keys[j];
        id[j+1] = id[j];
    }
 
    // Copy the middle key of y to this node
    keys[i] = y->keys[t-1];
    id[i] = y->id[t-1];
 
    // Increment count of keys in this node
    n = n + 1;
}
void NoB::setKey(int pos, ProductReview pr)
{
    keys[pos] = pr;
    setId(pos, &pr);
}
void NoB::setId(int pos, ProductReview *pr)
{
    id[pos] = pr->getUserId()+pr->getProductId();
}
void NoB::print()
{
    // There are n keys and n+1 children, traverse through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->print();
        cout << " " << id[i];
    }
 
    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->print();
 
}
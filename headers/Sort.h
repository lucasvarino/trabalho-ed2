#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include "ProductReview.h"

#include <iostream>
#include <string>

using namespace std;

class Sort
{
    private:
        void merge(ProductReview *vetor, int inicio, int meio, int fim);
        
    public:
        void mergeSort(ProductReview *vetor, int inicio, int fim);
        
};


#endif // SORT_H_INCLUDED
#ifndef PRODUCTREVIEW_H_INCLUDED
#define PRODUCTREVIEW_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class ProductReview
{
    private:
        string user_id;
        string product_id;
        float rating;
        string timestamp;
    public:
        ProductReview(string user_id, string product_id, float rating, string timestamp);
        ~ProductReview();
        void print();
};


#endif // PRODUCTREVIEW_H_INCLUDED

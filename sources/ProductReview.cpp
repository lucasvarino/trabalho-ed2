#include "ProductReview.h"

#include <iostream>
#include <string>

using namespace std;

ProductReview::ProductReview(string user_id, string product_id, float rating, string timestamp)
{
    this->user_id = user_id;
    this->product_id = product_id;
    this->rating = rating;
    this->timestamp = timestamp; //Validar a possibilidade de converter o timestamp
}

ProductReview::~ProductReview()
{
    
}

void ProductReview::print()
{
    cout << "- Product Review -" << endl << endl;
    cout << "User id: " << this->user_id << endl;
    cout << "Product id: " << this->product_id << endl;
    cout << "Rating: " << this->rating << endl;
    cout << "Timestamp: " << this->timestamp << endl;
}
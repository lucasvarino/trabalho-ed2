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
        ProductReview();
        ProductReview(string user_id, string product_id, float rating, string timestamp);
        ~ProductReview();

        string getUserId() { return this->user_id; };
        string getProductId() { return this->product_id; };
        float getRating() { return this->rating; };
        string getTimestamp() { return this->timestamp; };

        void setUserId(string userId) { this->user_id = userId; };
        void setProductId(string productId) { this->product_id = productId; };
        void setRating(float newRating) { this->rating = newRating; };
        void setTimestamp(string newTimestamp) { this->timestamp = newTimestamp; };

        void print();
        ProductReview* import(int n);
        static void createBinary(string dirCsv);
};


#endif // PRODUCTREVIEW_H_INCLUDED

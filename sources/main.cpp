#include <iostream>
#include <string>
#include "ProductReview.h"

using namespace std;

int main(int, char**) {
    std::cout << "Hello, world!\n";

    ProductReview* prod1 = new ProductReview("1", "1", 5.0, "10/10/2022");
    prod1->print();
}

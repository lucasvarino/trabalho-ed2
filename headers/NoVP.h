#ifndef NOVP_H_INCLUDED
#define NOVP_H_INCLUDED

#include <iostream>

using namespace std;


class NoVP{
    private:
        int data;
        NoVP *left;
        NoVP *right;
        char color;
        NoVP *parent;

    public:
        NoVP(int data);
        void setLeft(NoVP *left);
        void setRight(NoVP *right);
        void setColor(char color);
        void setParent(NoVP *parent);
        int getData();
        NoVP *getLeft();
        NoVP *getRight();
        char getColor();
        NoVP *getParent();
};






#endif // NOVP_H_INCLUDED
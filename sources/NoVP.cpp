#include "../headers/NoVp.h"
#include <iostream>

using namespace std;

NoVP::NoVP(int data){
    this->data = data;
    this->left = NULL;
    this->right = NULL;
    this->color = 'R';
    this->parent = NULL;
}

void NoVP::setLeft(NoVP *left){
    this->left = left;
}

void NoVP::setRight(NoVP *right){
    this->right = right;
}

void NoVP::setColor(char color){
    this->color = color;
}

void NoVP::setParent(NoVP *parent){
    this->parent = parent;
}

int NoVP::getData(){
    return this->data;
}

NoVP *NoVP::getLeft(){
    return this->left;
}

NoVP *NoVP::getRight(){
    return this->right;
}

char NoVP::getColor(){
    return this->color;
}

NoVP *NoVP::getParent(){
    return this->parent;
}


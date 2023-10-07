#include "position.h"

Position::Position(int x, int y): x(x), y(y){};

int Position::getX() const{
    return x;
};

int Position::getY() const{
    return y;
};

void Position::modifier_position(int a, int b){
    x = a;
    y = b;
};

bool Position::egale(const Position& autre) const{
    return (this->getX() == autre.getX()) and (this->getY() == autre.getY());
}


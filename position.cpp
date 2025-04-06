#include "position.h"

Position::Position(int x, int y): x(x), y(y){};

int Position::getX() const
{
    return x;
}

int Position::getY() const
{
    return y;
}

void Position::modifier_position(int a, int b){
    x = a;
    y = b;
}

bool Position::operator==(const Position& autre) const
{
    return (this->getX() == autre.getX()) && (this->getY() == autre.getY());
}

std::string Position::to_string() const{
    return std::to_string(x) + "," + std::to_string(y);
}


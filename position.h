
#ifndef _POSITION_
#define _POSITION_

class Position{
private:
    int x;
    int y;
public:
    Position(int x, int y);
    int getX() const;
    int getY() const;
    bool egale(const Position& autre) const;
    void modifier_position(int a, int b); // modifie la position x = a et y = b
};

#endif

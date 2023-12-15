
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
    bool egale(int x, int y) const;
    void modifier_position(int x, int y);
};

#endif

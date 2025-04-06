#ifndef _POSITION_
#define _POSITION_

#include <cstddef>
#include <functional>
#include <string>

class Position{
private:
    int x;
    int y;
public:
    Position(int x, int y);
    int getX() const;
    int getY() const;
    bool operator==(const Position& autre) const;
    std::string to_string() const;
    void modifier_position(int x, int y);
};

class HashPosition
{
public:
    size_t operator()(const Position pos) const {
        return std::hash<int>()(pos.getX()) ^ (std::hash<int>()(pos.getY()) << 1);
    }
};

#endif

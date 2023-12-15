#include "piece.h"
#include <iostream>
using namespace std;
#include <vector>
#include <QDebug>

#ifndef _TOUR_
#define _TOUR_

class Tour: public Piece{
public:
    Tour(int x, int y, Couleur couleur);
    ~Tour();
    vector<Position> positions_possibles(const array<array<Piece*, 8>, 8>& pieces) const override;
};

#endif

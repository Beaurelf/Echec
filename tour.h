#ifndef _TOUR_
#define _TOUR_

#include "piece.h"
#include <vector>
#include <QDebug>
using namespace std;

class Tour: public virtual Piece{
public:
    Tour(int x, int y, Couleur couleur, EchecModel* model);
    ~Tour();
    vector<Position> positions_possibles(const Pieces& pieces) const override;
};

#endif

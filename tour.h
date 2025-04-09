#ifndef _TOUR_
#define _TOUR_

#include "piece.h"
#include <vector>

using namespace std;

class Tour: public virtual Piece{
public:
    Tour(int x, int y, Couleur couleur);
    ~Tour();
    vector<Position> positions_possibles(const Pieces& pieces) const override;
    virtual Type get_type() const override;
};

#endif

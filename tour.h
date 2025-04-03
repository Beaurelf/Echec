#ifndef _TOUR_
#define _TOUR_

#include "piece.h"
#include <vector>
#include <QDebug>
using namespace std;

class Tour: public virtual Piece{
public:
    Tour(int x, int y, Couleur couleur);
    ~Tour();
    vector<Position> positions_possibles(const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const override;
};

#endif

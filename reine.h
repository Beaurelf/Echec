#include "piece.h"
using namespace std;
#include <vector>

#ifndef _REINE_
#define _REINE_

class Reine: public Piece{
public:
    Reine(int x, int y, Couleur couleur);
    ~Reine();
    vector<Position> positions_possibles(const array<array<Piece*, 8>, 8>& pieces) const override;
};

#endif

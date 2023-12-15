#include "piece.h"
using namespace std;
#include <vector>

#ifndef _CHEVALIER_
#define _CHEVALIER_

class Chevalier: public Piece{

public:
    Chevalier(int x, int y, Couleur couleur);
    ~Chevalier();
    vector<Position> positions_possibles(const array<array<Piece*, 8>, 8>& pieces) const override;
};

#endif

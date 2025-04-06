#ifndef _CHEVALIER_
#define _CHEVALIER_

#include "piece.h"
using namespace std;
#include <vector>

class Chevalier: public Piece{

public:
    Chevalier(int x, int y, Couleur couleur, EchecModel* model);
    ~Chevalier();
    vector<Position> positions_possibles(const Pieces& pieces) const override;
};

#endif

#include "piece.h"
#include <iostream>
using namespace std;
#include <vector>

#ifndef _SOLDAT_
#define _SOLDAT_

class Soldat: public Piece{
public:
    Soldat(int x, int y, Couleur couleur, int x_init, int y_init);
    ~Soldat();
    vector<Position> positions_possibles(array<array<Piece*, 8>, 8> pieces) const override;
    bool position_valide(const Position& position, array<array<Piece*, 8>, 8> pieces) const override;
private:
    int x_init;
    int y_init;
};

#endif

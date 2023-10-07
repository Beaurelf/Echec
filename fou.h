#include "piece.h"
using namespace std;
#include <vector>

#ifndef _FOU_
#define _FOU_

class Fou: public Piece{
public:
    Fou(int x, int y, Couleur couleur);
    ~Fou();
    vector<Position> positions_possibles(array<array<Piece*, 8>, 8> pieces) const override;
};

#endif

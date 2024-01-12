#include "piece.h"
using namespace std;
#include <vector>

#ifndef _FOU_
#define _FOU_

class Fou: public Piece{
public:
    Fou(int x, int y, Couleur couleur);
    ~Fou();
    vector<Position> positions_possibles(const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const override;
};

#endif

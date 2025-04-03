#ifndef _REINE_
#define _REINE_

#include "fou.h"
#include "piece.h"
#include "tour.h"
#include <vector>

using namespace std;

class Reine: public Tour, public Fou{
public:
    Reine(int x, int y, Couleur couleur);
    ~Reine();
    vector<Position> positions_possibles(const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const override;
};

#endif

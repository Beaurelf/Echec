#include "piece.h"
using namespace std;
#include <vector>

#ifndef _ROI_
#define _ROI_

class Roi: public Piece{
public:
    Roi(int x, int y, Couleur couleur);
    ~Roi();
    vector<Position> positions_possibles(const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const override;
};

#endif

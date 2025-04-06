#ifndef _ROI_
#define _ROI_

#include "piece.h"
using namespace std;
#include <vector>

class Roi: public Piece{
public:
    Roi(int x, int y, Couleur couleur, EchecModel* model);
    ~Roi();
    vector<Position> positions_possibles(const Pieces& pieces) const override;
};

#endif

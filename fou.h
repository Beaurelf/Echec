#ifndef _FOU_
#define _FOU_

#include "piece.h"
using namespace std;
#include <vector>

class Fou: public virtual Piece{
public:
    Fou(int x, int y, Couleur couleur);
    ~Fou();
    vector<Position> positions_possibles(const Pieces& pieces) const override;
    virtual Type get_type() const override;
};

#endif

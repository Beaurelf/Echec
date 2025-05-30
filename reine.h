#ifndef _REINE_
#define _REINE_

#include "fou.h"
#include "tour.h"
#include <vector>

using namespace std;

class Reine: public Tour, public Fou{
public:
    Reine(int x, int y, Couleur couleur);
    ~Reine();
    vector<Position> positions_possibles(const Pieces& pieces) const override;
    virtual Type get_type() const override;
};

#endif

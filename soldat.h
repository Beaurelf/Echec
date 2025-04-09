#ifndef _SOLDAT_
#define _SOLDAT_

#include "piece.h"
using namespace std;
#include <vector>

class Soldat: public Piece{
public:
    Soldat(int x, int y, Couleur couleur);
    ~Soldat();
    vector<Position> positions_possibles(const Pieces& pieces) const override;
    virtual Type get_type() const override;
    int get_y_init() const;
private:
    int x_init;
    int y_init;
};

#endif

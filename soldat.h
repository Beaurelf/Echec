#ifndef _SOLDAT_
#define _SOLDAT_

#include "piece.h"
using namespace std;
#include <vector>

class Soldat: public Piece{
public:
    Soldat(int x, int y, Couleur couleur, EchecModel* model);
    ~Soldat();
    vector<Position> positions_possibles(const Pieces& pieces) const override;
    bool position_valide(const Position& position, const Pieces& pieces) const override;
    int get_y_init() const;
private:
    int x_init;
    int y_init;
};

#endif

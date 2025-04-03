#ifndef _SOLDAT_
#define _SOLDAT_

#include "piece.h"
#include <iostream>
using namespace std;
#include <vector>

class Soldat: public Piece{
public:
    Soldat(int x, int y, Couleur couleur, int x_init, int y_init);
    ~Soldat();
    vector<Position> positions_possibles(const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const override;
    bool position_valide(const Position& position, const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const override;
    int get_y_init() const override;
private:
    int x_init;
    int y_init;
};

#endif

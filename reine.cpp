#include "reine.h"

Reine::Reine(int x, int y, Couleur couleur, EchecModel* model) :
    Piece(x, y, couleur, model), Tour(x, y, couleur, model), Fou(x, y, couleur, model)
{
    image = (couleur == BLANC) ? REINE_BLANC : REINE_NOIR;
};

Reine::~Reine(){};

vector<Position> Reine::positions_possibles(const Pieces& pieces) const {
    vector<Position> positions = Tour::positions_possibles(pieces);
    vector<Position> positions_fou = Fou::positions_possibles(pieces);
    for(auto it = positions_fou.begin(); it != positions_fou.end(); ++it) positions.push_back(*it);
    return positions;
};

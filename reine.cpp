#include "reine.h"

Reine::Reine(int x, int y, Couleur couleur) : Piece(x, y, couleur), Tour(x, y, couleur), Fou(x, y, couleur) {
    image = (couleur == BLANC) ? REINE_BLANC : REINE_NOIR;
    type = REINE;
};

Reine::~Reine(){};

vector<Position> Reine::positions_possibles(const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const {
    vector<Position> positions = Tour::positions_possibles(pieces);
    vector<Position> positions_fou = Fou::positions_possibles(pieces);
    for(auto it = positions_fou.begin(); it != positions_fou.end(); ++it) positions.push_back(*it);
    return positions;
};

#include "chevalier.h"

Chevalier::Chevalier(int x, int y, Couleur couleur) : Piece(x, y, couleur) {
    image = (couleur == BLANC) ? CHEVALIER_BLANC : CHEVALIER_NOIR;
};

Chevalier::~Chevalier(){};

Type Chevalier::get_type() const {
    return CHEVALIER;
}

vector<Position> Chevalier::positions_possibles(const Pieces& pieces) const {
    int x = position.getX();
    int y = position.getY();
    vector<Position> positions;

    // Déplacements possibles du chevalier
    vector<pair<int, int>> deplacements = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for (const auto& dep : deplacements) {
        int nouveauX = x + dep.first;
        int nouveauY = y + dep.second;

        // Vérifier si la position est à l'intérieur de l'échiquier
        if (nouveauX >= MIN_POSITION && nouveauX < MAX_POSITION && nouveauY >= MIN_POSITION && nouveauY < MAX_POSITION) {
            Position pos(nouveauX, nouveauY);
            if (this->position_valide(pos, pieces)) {
                positions.push_back(pos);
            }
        }
    }

    return positions;
};

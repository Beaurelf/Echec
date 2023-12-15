#include "chevalier.h"

Chevalier::Chevalier(int x, int y, Couleur couleur) : Piece(x, y, couleur) {
    image = (couleur == BLANC) ? Utils::CHEVALIER_BLANC : Utils::CHEVALIER_NOIR;
    type = CHEVALIER;
};

Chevalier::~Chevalier(){};

vector<Position> Chevalier::positions_possibles(const array<array<Piece*, 8>, 8>& pieces) const {
    int x = position.getX();
    int y = position.getY();
    vector<Position> positions;

    // Déplacements possibles du chevalier
    vector<pair<int, int>> deplacements = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for (const auto& dep : deplacements) {
        int nouveauX = x + dep.first;
        int nouveauY = y + dep.second;

        // Vérifier si la position est à l'intérieur de l'échiquier
        if (nouveauX >= 0 && nouveauX < 8 && nouveauY >= 0 && nouveauY < 8) {
            Position pos(nouveauX, nouveauY);
            if (this->position_valide(pos, pieces)) {
                positions.push_back(pos);
            }
        }
    }

    return positions;
};

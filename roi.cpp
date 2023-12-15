#include "roi.h"

Roi::Roi(int x, int y, Couleur couleur) : Piece(x, y, couleur) {
    image = (couleur == BLANC) ? Utils::ROI_BLANC : Utils::ROI_NOIR;
    type = ROI;
};

Roi::~Roi(){};

vector<Position> Roi::positions_possibles(const array<array<Piece*, 8>, 8>& pieces) const {
    int x = position.getX();
    int y = position.getY();
    vector<Position> positions;

    // Directions dans lesquelles le roi peut se déplacer
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    for (const auto& dir : directions) {
        int nouveauX = x + dir.first;
        int nouveauY = y + dir.second;

        // Vérifier si la nouvelle position est à l'intérieur de l'échiquier
        if (nouveauX >= 0 && nouveauX < 8 && nouveauY >= 0 && nouveauY < 8) {
            Position pos(nouveauX, nouveauY);
            if (this->position_valide(pos, pieces)) {
                positions.push_back(pos);
            }
        }
    }

    return positions;
};

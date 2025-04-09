#include "roi.h"

Roi::Roi(int x, int y, Couleur couleur) : Piece(x, y, couleur) {
    image = (couleur == BLANC) ? ROI_BLANC : ROI_NOIR;
};

Roi::~Roi(){};

Type Roi::get_type() const {
    return ROI;
}

vector<Position> Roi::positions_possibles(const Pieces& pieces) const {
    int x = position.getX();
    int y = position.getY();
    vector<Position> positions;

    // Directions dans lesquelles le roi peut se déplacer
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    for (const auto& dir : directions) {
        int nouveauX = x + dir.first;
        int nouveauY = y + dir.second;

        // Vérifier si la nouvelle position est à l'intérieur de l'échiquier
        if (nouveauX >= MIN_POSITION && nouveauX < MAX_POSITION && nouveauY >= MIN_POSITION && nouveauY < MAX_POSITION) {
            Position pos(nouveauX, nouveauY);
            if (this->position_valide(pos, pieces)) {
                positions.push_back(pos);
            }
        }
    }

    return positions;
};

#include "tour.h"

Tour::Tour(int x, int y, Couleur couleur) : Piece(x, y, couleur) {
    image = (couleur == BLANC) ? Utils::TOUR_BLANC : Utils::TOUR_NOIR;
    type = TOUR;
};

Tour::~Tour(){};

vector<Position> Tour::positions_possibles(const array<array<Piece*, 8>, 8>& pieces) const {
    int x = position.getX();
    int y = position.getY();
    vector<Position> positions;

    // Directions : droite, gauche, bas, haut
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

    for (const auto& dir : directions) {
        int dx = dir.first;
        int dy = dir.second;
        int i = 1;

        while (true) {
            int nouveauX = x + i * dx;
            int nouveauY = y + i * dy;

            // Vérifier si la position est à l'intérieur de l'échiquier
            if (nouveauX < 0 || nouveauX >= 8 || nouveauY < 0 || nouveauY >= 8)
                break; // Sortie de l'échiquier

            Position pos(nouveauX, nouveauY);
            if (this->position_valide(pos, pieces)) {
                positions.push_back(pos);
                if (peut_manger(pos, pieces)) {
                    break; // Arrêtez de chercher dans cette direction après avoir trouvé une pièce à manger
                }
            } else
                break; // Bloqué par une pièce, arrêtez de chercher dans cette direction
            ++i;
        }
    }

    return positions;
};

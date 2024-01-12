#include "reine.h"

Reine::Reine(int x, int y, Couleur couleur) : Piece(x, y, couleur) {
    image = (couleur == BLANC) ? REINE_BLANC : REINE_NOIR;
    type = REINE;
};

Reine::~Reine(){};

vector<Position> Reine::positions_possibles(const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const {
    int x = position.getX();
    int y = position.getY();
    vector<Position> positions;

    // Directions: droite, gauche, bas, haut, diagonales
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    for (const auto& dir : directions) {
        int dx = dir.first;
        int dy = dir.second;
        int i = 1;

        while (true) {
            int nouveauX = x + i * dx;
            int nouveauY = y + i * dy;

            if (nouveauX < MIN_POSITION || nouveauX >= MAX_POSITION || nouveauY < MIN_POSITION || nouveauY >= MAX_POSITION) {
                break; // Sortie de l'échiquier
            }

            Position pos(nouveauX, nouveauY);
            if (position_valide(pos, pieces)) {
                positions.push_back(pos);
                if (peut_manger(pos, pieces)) {
                    break; // Arrêtez de chercher dans cette direction après avoir trouvé une pièce à manger
                }
            } else {
                break; // Bloqué par une pièce, arrêtez de chercher dans cette direction
            }
            ++i;
        }
    }

    return positions;
};

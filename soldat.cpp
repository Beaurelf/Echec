#include "soldat.h"

Soldat::Soldat(int x, int y, Couleur couleur, int x_init, int y_init) : Piece(x, y, couleur), x_init(x_init), y_init(y_init) {
    image = (couleur == BLANC) ? PION_BLANC : PION_NOIR;
    type = SOLDAT;
};

Soldat::~Soldat(){};

bool Soldat::position_valide(const Position& position,const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const{
    return not ((pieces[position.getY()][position.getX()] != nullptr) and
            (position.egale(pieces[position.getY()][position.getX()]->get_position())));
}

int Soldat::get_y_init() const
{
    return y_init;
}

vector<Position> Soldat::positions_possibles(const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const{
    int x(position.getX());
    int y(position.getY());
    vector<Position> positions;
    int direction = (couleur == NOIR) ? 1 : -1;

    Position pos(x, y + direction);
    if(this->position_valide(pos, pieces)){
        positions.push_back(pos);
        if(y == y_init){
            Position pos(x, y + 2 * direction);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
    }

    vector<Position> positionsDiagonales = {{x - 1, y + direction}, {x + 1, y + direction}};
    for (const auto& pos : positionsDiagonales) {
        for (auto& p : pieces) {
            for (auto& piece : p) {
                if((piece!=nullptr) and (piece->get_couleur() != this->get_couleur())){
                    if(pos.egale(piece->get_position())){
                        positions.push_back(pos);
                    }
                }
            }
        }
    }

    return positions;
};


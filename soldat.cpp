#include "soldat.h"

Soldat::Soldat(int x, int y, Couleur couleur) : Piece(x, y, couleur), y_init(y) {
    image = (couleur == BLANC) ? PION_BLANC : PION_NOIR;
};

Soldat::~Soldat(){};

Type Soldat::get_type() const {
    return SOLDAT;
}

int Soldat::get_y_init() const {
    return position_initiale.getY();
}

vector<Position> Soldat::positions_possibles(const Pieces& pieces) const{
    int x(position.getX());
    int y(position.getY());
    vector<Position> positions;
    int direction = (couleur == NOIR) ? 1 : -1;

    Position pos(x, y + direction);
    auto it = pieces.find(pos);
    if(this->position_valide(pos, pieces) && it->second == nullptr){
        positions.push_back(pos);
        it = pieces.find(pos);
        if(position_initiale.getY() == y){
            Position pos(x, y + 2 * direction);
            if(this->position_valide(pos, pieces) && it->second == nullptr){
                positions.push_back(pos);
            }
        }
    }

    vector<Position> positionsDiagonales = {{x - 1, y + direction}, {x + 1, y + direction}};
    for (const auto& pos : positionsDiagonales) {
        auto it = pieces.find(pos);
        if(it != pieces.end())
            if(it->second != nullptr && it->second->get_couleur() != get_couleur()) positions.push_back(pos);
    }

    return positions;
};


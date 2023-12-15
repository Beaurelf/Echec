#include "soldat.h"

Soldat::Soldat(int x, int y, Couleur couleur, int x_init, int y_init) : Piece(x, y, couleur), x_init(x_init), y_init(y_init) {
    image = (couleur == BLANC) ? Utils::PION_BLANC : Utils::PION_NOIR;
    type = SOLDAT;
};

Soldat::~Soldat(){};

bool Soldat::position_valide(const Position& position,const array<array<Piece*, 8>, 8>& pieces) const{
    return not ((pieces[position.getY()][position.getX()] != nullptr) and
            (position.egale(pieces[position.getY()][position.getX()]->get_position())));
}

int Soldat::get_y_init() const
{
    return y_init;
}

vector<Position> Soldat::positions_possibles(const array<array<Piece*, 8>, 8>& pieces) const{
    int x(position.getX());
    int y(position.getY());
    vector<Position> positions;
    bool p(true); // regarder s'il y'a une piece devant le pion

    if(couleur == NOIR){
        Position pos(x,y+1);
        if(this->position_valide(pos, pieces)){
            positions.push_back(pos);
        }else{
            p = false;
        }

        if(x == x_init and y == y_init and p){
            Position pos(x,y+2);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }

        Position pos1(x+1,y+1); // deplacement diagonale si on peut manger
        for (auto p : pieces) {
            for (auto const& piece : p) {
                if((piece!=nullptr) and (piece->get_couleur() != this->get_couleur())){
                    if(pos1.egale(piece->get_position())){
                        positions.push_back(pos1);
                    }
                }
            }
        }

        Position pos2(x-1,y+1); // deplacement diagonale si on peut manger
        for (auto p : pieces) {
            for (auto const& piece : p) {
                if((piece!=nullptr) and (piece->get_couleur() != this->get_couleur())){
                    if(pos2.egale(piece->get_position())){
                        positions.push_back(pos2);
                    }
                }
            }
        }
    }
    else
    {
        Position pos(x,y-1);
        if(this->position_valide(pos, pieces)){
            positions.push_back(pos);
        }else{
            p = false;
        }

        if(x == x_init and y == y_init and p){
            Position pos(x,y-2);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }

        Position pos1(x+1,y-1); // deplacement diagonale si on peut manger
        for (auto p : pieces) {
            for (auto const& piece : p) {
                if((piece!=nullptr) and (piece->get_couleur() != this->get_couleur())){
                    if(pos1.egale(piece->get_position())){
                        positions.push_back(pos1);
                    }
                }
            }
        }

        Position pos2(x-1,y-1); // deplacement diagonale si on peut manger
        for (auto p : pieces) {
            for (auto const& piece : p) {
                if((piece!=nullptr) and (piece->get_couleur() != this->get_couleur())){
                    if(pos2.egale(piece->get_position())){
                        positions.push_back(pos2);
                    }
                }
            }
        }
    }

    return positions;
};


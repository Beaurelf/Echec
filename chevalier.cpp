#include "chevalier.h"

Chevalier::Chevalier(int x, int y, Couleur couleur) : Piece(x, y, couleur) {
    image = (couleur == BLANC) ? Utils::CHEVALIER_BLANC : Utils::CHEVALIER_NOIR;
    type = CHEVALIER;
};

Chevalier::~Chevalier(){};

vector<Position> Chevalier::positions_possibles(const array<array<Piece*, 8>, 8>& pieces) const{
    int x(position.getX());
    int y(position.getY());
    vector<Position> positions;


    if(x + 2 <= 7){
        if(y - 1 >= 0){
            Position pos(x+2, y-1);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
        if(y + 1 <= 7){
            Position pos(x+2, y+1);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
    }

    if(x - 2 >= 0){
        if(y - 1 >= 0){
            Position pos(x-2, y-1);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
        if(y + 1 <= 7){
            Position pos(x-2, y+1);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
    }

    if(y + 2 <= 7){
        if(x - 1 >= 0){
            Position pos(x-1, y+2);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
        if(x + 1 <= 7){
            Position pos(x+1, y+2);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
    }

    if(y - 2 >= 0){
        if(x - 1 >= 0){
            Position pos(x-1, y-2);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
        if(x + 1 <= 7){
            Position pos(x+1, y-2);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
    }

    return positions;
};

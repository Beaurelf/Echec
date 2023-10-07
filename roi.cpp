#include "roi.h"

Roi::Roi(int x, int y, Couleur couleur) : Piece(x, y, couleur) {
    if(couleur == BLANC){
        image = Utils::ROI_BLANC;
    }else{
        image = Utils::ROI_NOIR;
    };
};

Roi::~Roi(){};

vector<Position> Roi::positions_possibles(array<array<Piece*, 8>, 8> pieces) const{
    int x(position.getX());
    int y(position.getY());
    vector<Position> positions;

    if(x + 1 <= 7){
        Position pos(x+1, y);
        if(this->position_valide(pos, pieces)){
            positions.push_back(pos);
        }
        if(y + 1 <= 7){
            Position pos(x+1, y+1);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }

        if(y - 1 >= 0){
            Position pos(x+1, y-1);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
    }

    if(x - 1 >= 0){
        Position pos(x-1, y);
        if(this->position_valide(pos, pieces)){
            positions.push_back(pos);
        }

        if(y + 1 <= 7){
            Position pos(x-1, y+1);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }

        if(y - 1 >= 0){
            Position pos(x-1, y-1);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
            }
        }
    }

    if(y + 1 <= 7){
        Position pos(x, y+1);
        if(this->position_valide(pos, pieces)){
            positions.push_back(pos);
        }
    }

    if(y - 1 >= 0){
        Position pos(x, y-1);
        if(this->position_valide(pos, pieces)){
            positions.push_back(pos);
        }
    }

    return positions;
};

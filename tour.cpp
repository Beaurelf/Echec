#include "tour.h"

Tour::Tour(int x, int y, Couleur couleur) : Piece(x, y, couleur) {
    image = (couleur == BLANC) ? Utils::TOUR_BLANC : Utils::TOUR_NOIR;
    type = TOUR;
};

Tour::~Tour(){};

vector<Position> Tour::positions_possibles(const array<array<Piece*, 8>, 8>& pieces) const{
    int x(position.getX());
    int y(position.getY());
    vector<Position> positions;
    int i(1);
    bool p_1(true);
    bool p_2(true);
    bool p_3(true);
    bool p_4(true);

    while((x+i <= 7) or (y+i <= 7) or (x-i >= 0) or (y-i >= 0)){
        if(x + i <= 7  and p_1){ // DROITE
            Position pos(x+i, y);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
                if(peut_manger(pos, pieces)){
                    p_1 = false;
                }
            }else{
                p_1 = false;
            }
        }

        if(x - i >= 0  and p_2){ // GAUCHE
            Position pos(x-i, y);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
                if(peut_manger(pos, pieces)){
                    p_2 = false;
                }
            }else{
                p_2 = false;
            }
        }

        if(y - i >= 0  and p_3){ // EN BAS
            Position pos(x, y-i);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
                if(peut_manger(pos, pieces)){
                    p_3 = false;
                }
            }else{
                p_3 = false;
            }
        }

        if(y + i <= 7 and p_4){ //  EN HAUT
            Position pos(x, y+i);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
                if(peut_manger(pos, pieces)){
                    p_4 = false;
                }
            }else{
                p_4 = false;
            }
        }
        if((p_1 == false) && (p_2 == false) && (p_3 == false) && (p_4 == false)){
            break;
        }
        ++i;
    }
    return positions;
};

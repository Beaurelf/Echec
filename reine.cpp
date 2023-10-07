#include "reine.h"

Reine::Reine(int x, int y, Couleur couleur) : Piece(x, y, couleur) {
    if(couleur == BLANC){
        image = Utils::REINE_BLANC;
    }else{
        image = Utils::REINE_NOIR;
    };
};

Reine::~Reine(){};

vector<Position> Reine::positions_possibles(array<array<Piece*, 8>, 8> pieces) const{
    int x(position.getX());
    int y(position.getY());
    vector<Position> positions;

    bool p_1(true);
    bool p_2(true);
    bool p_3(true);
    bool p_4(true);

    int i(1);

    while((x+i <= 7) or (y+i <= 7) or (x-i >= 0) or (y-i >= 0)){
        if(x + i <= 7  and p_1){ // DROITE
            Position pos(x+i, y);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
                if(manger(pos, pieces)){
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
                if(manger(pos, pieces)){
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
                if(manger(pos, pieces)){
                    p_3 = false;
                }
            }else{
                p_3 = false;
            }
        }

        if(y + i <= 7  and p_4){ //  EN HAUT
            Position pos(x, y+i);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
                if(manger(pos, pieces)){
                    p_4 = false;
                }
            }else{
                p_4 = false;
            }
        }
        if((p_1 == false) and (p_2 == false) and (p_3 == false) and (p_4 == false)){
            break;
        }
        ++i;
    }

    // reaffectation des variables initiales
    i = 1;
    p_1 = true;
    p_2 = true;
    p_3 = true;
    p_4 = true;

    // nous permettra d'avoir les differentes positions en soustrayant ajoutant le meme nombre a l'abscisses et a l'ordonne
    while (((x + i <= 7) and (y + i <= 7)) or ((x - i >= 0) and (y + i <= 7)) or ((x + i <= 7) and (y - i >= 0)) or ((x - i >= 0) and (y - i >= 0)))
    {
        if((x + i <= 7) and (y + i <= 7) and p_1){ // DROITE EN HAUT
            Position pos(x+i, y+i);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
                if(manger(pos, pieces)){
                    p_1 = false;
                }
            }else{
                p_1 = false;
            }
        }

        if((x - i >= 0) and (y + i <= 7) and p_2){ // GAUCHE EN HAUT
            Position pos(x-i, y+i);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
                if(manger(pos, pieces)){
                    p_2 = false;
                }
            }else{
                p_2 = false;
            }
        }

        if((x + i <= 7) and (y - i >= 0) and p_3){ // DROITE EN BAS
            Position pos(x+i, y-i);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
                if(manger(pos, pieces)){
                    p_3 = false;
                }
            }else{
                p_3 = false;
            }
        }

        if((x - i >= 0) and (y - i >= 0) and p_4){ // GAUCHE EN BAS
            Position pos(x-i, y-i);
            if(this->position_valide(pos, pieces)){
                positions.push_back(pos);
                if(manger(pos, pieces)){
                    p_4 = false;
                }
            }else{
                p_4 = false;
            }
        }
        if((p_1 == false) and (p_2 == false) and (p_3 == false) and (p_4 == false)){
            break;
        }
        ++i;
    }

    return positions;
};

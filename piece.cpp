#include "piece.h"
#include <string>

Piece::Piece(int x, int y, Couleur couleur) : position(x, y), couleur(couleur) {};

Position Piece::get_position() const{
    return position;
}

bool Piece::position_valide(const Position& position, array<array<Piece*, 8>, 8> pieces) const{ //utiliser par positions_possibles
    return not ((pieces[position.getY()][position.getX()] != nullptr) and
            (pieces[position.getY()][position.getX()]->get_couleur() == this->get_couleur()));
}

// verifier si le deplacement est valide
bool Piece::deplacement_valide(int x, int y, array<array<Piece*, 8>, 8> pieces) const{
    // verifie si le couple (x,y) est une position possible lors du prochain deplacement
    for (auto const& pos : positions_possibles(pieces))
    {
        if((x == pos.getX()) and (y == pos.getY())){
            return true;
        }
    }
    return false;
};

bool Piece::manger(const Position& position,  array<array<Piece*, 8>, 8> pieces) const{
    //Utiliser dans game.cpp pour marquer les pieces pouvant etre manger par une couleur rouge
    return ((pieces[position.getY()][position.getX()] != nullptr) and
            (pieces[position.getY()][position.getX()]->get_couleur() != this->get_couleur()) and
            (position.egale(pieces[position.getY()][position.getX()]->get_position())));
}

Couleur Piece::get_couleur() const {
    return couleur;
};

string Piece::get_image() const {
    return image;
}

// deplacer piece (utilise deplacement_valide)
void Piece::se_deplacer(int x, int y, array<array<Piece*, 8>, 8> pieces)
{
    if (deplacement_valide(x, y, pieces)){
        position.modifier_position(x, y);
    }
};

Piece::~Piece(){};

#include "piece.h"
#include <string>

Piece::Piece(int x, int y, Couleur couleur) :
    position(x, y), position_initiale(x, y), ancienne_position(x, y), couleur(couleur){}

Position Piece::get_position() const{
    return position;
}

Position Piece::get_ancienne_position() const
{
    return ancienne_position;
}

bool Piece::position_valide(const Position& position, const Pieces& pieces) const{
    //utiliser par positions_possibles
    auto it = pieces.find(position);
    if(it == pieces.end()) return false;
    return !(it->second != nullptr && it->second->get_couleur() == this->get_couleur());
}

// verifier si le deplacement est valide
bool Piece::deplacement_valide(const Position& pos, const Pieces& pieces) const
{
    // verifie si le couple (x,y) est une position possible lors du prochain deplacement
    auto deplacement_possibles = positions_possibles(pieces);
    auto it = find_if(deplacement_possibles.begin(), deplacement_possibles.end(), [&](const Position& p){
        return pos == p;
    });
    return it != deplacement_possibles.end();
}

bool Piece::peut_manger(const Position& position,  const Pieces& pieces) const
{
    auto it = pieces.find(position);
    if(it == pieces.end()) return false;
    return ((it->second != nullptr) && (it->second->get_couleur() != this->get_couleur()) && (position == it->second->get_position()));
}

Couleur Piece::get_couleur() const
{
    return couleur;
}

string Piece::get_image() const
{
    return image;
}

// deplacer piece (utilise deplacement_valide)
void Piece::se_deplacer(const Position& pos, const Pieces& pieces)
{
    if (deplacement_valide(pos, pieces))
    {
        ancienne_position = position;
        position.modifier_position(pos.getX(), pos.getY());
    }
}

void Piece::retour_position()
{
    position.modifier_position(ancienne_position.getX(), ancienne_position.getY());
}

Piece::~Piece(){}

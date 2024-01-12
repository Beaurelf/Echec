#include "piece.h"
#include <string>

Piece::Piece(int x, int y, Couleur couleur) : position(x, y), ancienne_position(x, y), couleur(couleur) {}

Position Piece::get_position() const{
    return position;
}

Position Piece::get_ancienne_position() const
{
    return ancienne_position;
}

bool Piece::position_valide(const Position& position, const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const{ //utiliser par positions_possibles
    return !((pieces[position.getY()][position.getX()] != nullptr) &&
            (pieces[position.getY()][position.getX()]->get_couleur() == this->get_couleur()));
}

// verifier si le deplacement est valide
bool Piece::deplacement_valide(int x, int y, const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const
{
    // verifie si le couple (x,y) est une position possible lors du prochain deplacement
    auto deplacement_possibles = positions_possibles(pieces);
    auto it = find_if(deplacement_possibles.begin(), deplacement_possibles.end(), [&](const Position& pos){
        return pos.egale(x, y);
    });
    return it != deplacement_possibles.end();
}

bool Piece::peut_manger(const Position& position,  const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const
{
    return ((pieces[position.getY()][position.getX()] != nullptr) &&
            (pieces[position.getY()][position.getX()]->get_couleur() != this->get_couleur()) &&
            (position.egale(pieces[position.getY()][position.getX()]->get_position())));
}

Couleur Piece::get_couleur() const
{
    return couleur;
}

string Piece::get_image() const
{
    return image;
}

Type Piece::get_type() const
{
    return type;
}

int Piece::get_y_init() const
{
    return 0;
}

// deplacer piece (utilise deplacement_valide)
void Piece::se_deplacer(int x, int y, const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces)
{
    if (deplacement_valide(x, y, pieces))
    {
        ancienne_position = position;
        position.modifier_position(x, y);
    }
}

void Piece::retour_position()
{
    position.modifier_position(ancienne_position.getX(), ancienne_position.getY());
}

Piece::~Piece(){}

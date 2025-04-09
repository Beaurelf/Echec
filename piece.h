#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "position.h"
#include "utils.h"

using namespace std;
using namespace Utils;

class Piece
{
public:
    Piece() = delete;
    Piece(int x, int y, Couleur couleur);
    virtual ~Piece();

    // deplacer piece (utilise deplacement_valide) et sa nouvelle position pos
    void se_deplacer(const Position& pos, const Pieces& pieces);

    // differentes positions que la piece peut occuper si elle se deplace
    virtual vector<Position> positions_possibles(const Pieces& pieces) const = 0;

    virtual Type get_type() const = 0;

    // verifie si la position ne correspond pas a la position d'un autre pion du meme joueur
    virtual bool position_valide(const Position& pos, const Pieces& pieces) const;

    // verifier si la position x, y est valide (figure parmi les positions_possibles)
    bool deplacement_valide(const Position& pos, const Pieces& pieces) const;

    // renvoie vrai si on mange une piece a cette position
    bool peut_manger(const Position& position,  const Pieces& pieces) const;

    //retourne la position de la piece
    Position get_position() const;

    Position get_ancienne_position() const;

    Couleur get_couleur() const;

    string get_image() const;

     // retourne à la position juste avant le déplacement
    void retour_position();

protected:
    Position position;
    Position position_initiale;
    Position ancienne_position;
    Couleur couleur;
    string image;
};

#endif

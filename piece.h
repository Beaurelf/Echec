#ifndef _PIECE_
#define _PIECE_
#include <vector>
#include "position.h"
#include "utils.h"
#include <array>

using namespace std;
using namespace Utils;

class Piece
{
public:
    Piece() = delete;
    Piece(int x, int y, Couleur couleur);
    virtual ~Piece();

    void se_deplacer(int x, int y, const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces); // deplacer piece (utilise deplacement_valide) et sa nouvelle position devient x, y

    virtual vector<Position> positions_possibles(const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const = 0; // differentes positions que la piece peut occuper si elle se deplace

    virtual bool position_valide(const Position& position, const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const; // verifie si la position ne correspond pas a la position
                                                                                             // d'un autre pion du meme joueur
    virtual int get_y_init() const;

    bool deplacement_valide(int x, int y, const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const; // verifier si la position x, y est valide (figure parmi les positions_possibles)

    bool peut_manger(const Position& position,  const array<array<Piece*, TAILLE_PIECES>, TAILLE_PIECES>& pieces) const; // renvoie vrai si on mange une piece a cette position

    Position get_position() const; //retourne la position de la piece

    Position get_ancienne_position() const;

    Couleur get_couleur() const;

    string get_image() const;

    Type get_type() const;

    void retour_position(); // retourne à la position juste avant le déplacement

protected:
    Position position;
    Position ancienne_position;
    Couleur couleur;
    string image;
    Type type;
};

#endif

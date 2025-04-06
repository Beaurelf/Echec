#pragma once

#include <vector>
#include <QGraphicsObject>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "position.h"
#include "utils.h"

using namespace std;
using namespace Utils;

class EchecModel;

class Piece : public QGraphicsObject
{
    Q_OBJECT
public:
    Piece() = delete;
    Piece(int x, int y, Couleur couleur, EchecModel* model, QGraphicsObject *parent = nullptr);
    virtual ~Piece();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void mise_a_jour_rendu();

    // deplacer piece (utilise deplacement_valide) et sa nouvelle position pos
    void se_deplacer(const Position& pos, const Pieces& pieces);

    // differentes positions que la piece peut occuper si elle se deplace
    virtual vector<Position> positions_possibles(const Pieces& pieces) const = 0;

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
    EchecModel* echec_model_;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
signals:
    void piece_appuye(int x, int y);
    void piece_relache(int x, int y);
};

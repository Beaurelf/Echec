#ifndef PIECEITEM_H
#define PIECEITEM_H

#include <QGraphicsObject>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "echec_model.h"
#include "utils.h"

using namespace Utils;

class PieceItem : public QGraphicsObject
{
    Q_OBJECT
public:
    PieceItem(Piece* piece, EchecModel* model, QGraphicsObject* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void deplacer();

private:
    Piece* piece_;
    EchecModel* echec_model_;
    Couleur couleur_;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void piece_appuye(int x, int y);
    void piece_relache(int x, int y);
};

#endif // PIECEITEM_H

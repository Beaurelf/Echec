#ifndef CASE_ECHEQUIER_H
#define CASE_ECHEQUIER_H

#include <QGraphicsObject>
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>

class CaseEchequier : public QGraphicsObject
{
    Q_OBJECT
public:
    CaseEchequier(int x, int y, QString c, QGraphicsObject *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void ajouter_marqueur(bool est_mangeable = false);
    void retirer_marqueur();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QColor couleur_;
    bool marqueur_actif_;
    bool est_mangeable_;
signals:
    void case_pressee(int x, int y);
};

#endif // CASE_ECHEQUIER_H

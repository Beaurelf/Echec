#ifndef CASE_ECHEQUIER_H
#define CASE_ECHEQUIER_H

#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class CaseEchequier : public QGraphicsItem
{
public:
    CaseEchequier(int x, int y, QString c, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void ajouter_marqueur(bool est_mangeable = false);
    void retirer_marqueur();
private:
    QColor couleur_;
    bool marqueur_actif_;
    bool est_mangeable_;
};

#endif // CASE_ECHEQUIER_H

#include "case_echequier.h"
#include "utils.h"

using namespace Utils;

CaseEchequier::CaseEchequier(int x, int y, QString c, QGraphicsItem* p): QGraphicsItem(p), couleur_(c), marqueur_actif_(false) {
    setPos(x * TAILLE_CASE_ECHIQUIER, y * TAILLE_CASE_ECHIQUIER);
}

QRectF CaseEchequier::boundingRect() const {
    return QRectF(0, 0, TAILLE_CASE_ECHIQUIER, TAILLE_CASE_ECHIQUIER);
}

void CaseEchequier::ajouter_marqueur(bool est_mangeable) {
    // Mémoriser l'état du marqueur
    marqueur_actif_ = true;
    est_mangeable_ = est_mangeable;
    // Déclencher le rafraîchissement de l'affichage
    update();
}

void CaseEchequier::retirer_marqueur() {
    marqueur_actif_ = false;
    update();
}

void CaseEchequier::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QRectF rec = boundingRect();

    // Dessiner le fond de la case avec sa couleur normale
    QBrush brush(couleur_);
    painter->fillRect(rec, brush);

    // Si un marqueur est actif, l'afficher selon son type
    if (marqueur_actif_) {
        if (est_mangeable_) {
            const QColor belge(COULEUR_BELGE);
            QBrush marqueurBrush(belge);
            painter->fillRect(rec, marqueurBrush);
        } else {
            // Cercle de marqueur pour les déplacements possibles
            QPointF centre(rec.x() + TAILLE_CASE_ECHIQUIER / 2, rec.y() + TAILLE_CASE_ECHIQUIER / 2);
            painter->setPen(Qt::NoPen);
            QRadialGradient gradient(centre, TAILLE_CASE_ECHIQUIER / 5);
            gradient.setColorAt(0, QColor(COULEUR_NOIR));
            gradient.setColorAt(1, Qt::transparent);
            painter->setBrush(QBrush(gradient));
            painter->drawEllipse(centre, TAILLE_CASE_ECHIQUIER / 5, TAILLE_CASE_ECHIQUIER / 5);
        }
    }
}


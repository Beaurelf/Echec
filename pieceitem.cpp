#include "pieceitem.h"

PieceItem::PieceItem(Piece *piece, EchecModel *model, QGraphicsObject *parent) :
    QGraphicsObject(parent), piece_(piece), echec_model_(model), couleur_(piece->get_couleur())
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    setZValue(1);
    setPos(piece->get_position().getX() * TAILLE_CASE_ECHIQUIER, piece->get_position().getY() * TAILLE_CASE_ECHIQUIER);
}

QRectF PieceItem::boundingRect() const {
    return QRectF(0, 0, TAILLE_CASE_ECHIQUIER, TAILLE_CASE_ECHIQUIER);
}

void PieceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    qreal iconX = (TAILLE_CASE_ECHIQUIER - TAILLE_ICON_CASE_ECHIQUIER) / 2;
    qreal iconY = (TAILLE_CASE_ECHIQUIER - TAILLE_ICON_CASE_ECHIQUIER) / 2;
    QPixmap icon(QString::fromStdString(piece_->get_image()));
    painter->drawPixmap(iconX, iconY, TAILLE_ICON_CASE_ECHIQUIER, TAILLE_ICON_CASE_ECHIQUIER, icon);
}

void PieceItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(echec_model_ && echec_model_->get_joueur_courant() != couleur_){
        event->ignore();
        return;
    }
    QGraphicsObject::mousePressEvent(event);
    setCursor(Qt::ClosedHandCursor);
    QPointF scenePos = event->scenePos();
    int x = static_cast<int>(scenePos.x() / TAILLE_CASE_ECHIQUIER);
    int y = static_cast<int>(scenePos.y() / TAILLE_CASE_ECHIQUIER);
    emit piece_appuye(x, y);
}

void PieceItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if(echec_model_ && echec_model_->get_joueur_courant() != couleur_){
        event->ignore();
        return;
    }
    QGraphicsObject::mouseReleaseEvent(event);
    setCursor(Qt::OpenHandCursor);
    QPointF scenePos = event->scenePos();
    int x = static_cast<int>(scenePos.x() / TAILLE_CASE_ECHIQUIER);
    int y = static_cast<int>(scenePos.y() / TAILLE_CASE_ECHIQUIER);
    const Position pos = Position(x, y);
    qDebug() << pos.to_string();
    if(piece_->get_position() == pos || !piece_->deplacement_valide(pos, echec_model_->get_pieces()))
    {
        deplacer();
        return;
    }
    emit piece_relache(x, y);
}

void PieceItem::deplacer() {
    setPos(piece_->get_position().getX() * TAILLE_CASE_ECHIQUIER, piece_->get_position().getY() * TAILLE_CASE_ECHIQUIER);
    update();
}

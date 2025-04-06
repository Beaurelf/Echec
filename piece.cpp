#include "piece.h"
#include "echec_model.h"
#include <string>

Piece::Piece(int x, int y, Couleur couleur, EchecModel* model, QGraphicsObject *parent) :
    QGraphicsObject(parent), position(x, y), position_initiale(x, y), ancienne_position(x, y), couleur(couleur), echec_model_(model)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    setZValue(1);
    setPos(x * TAILLE_CASE_ECHIQUIER, y * TAILLE_CASE_ECHIQUIER);
}

QRectF Piece::boundingRect() const {
    return QRectF(0, 0, TAILLE_CASE_ECHIQUIER, TAILLE_CASE_ECHIQUIER);
}

void Piece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    qreal iconX = (TAILLE_CASE_ECHIQUIER - TAILLE_ICON_CASE_ECHIQUIER) / 2;
    qreal iconY = (TAILLE_CASE_ECHIQUIER - TAILLE_ICON_CASE_ECHIQUIER) / 2;
    QPixmap icon(QString::fromStdString(image));
    painter->drawPixmap(iconX, iconY, TAILLE_ICON_CASE_ECHIQUIER, TAILLE_ICON_CASE_ECHIQUIER, icon);
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(echec_model_ && echec_model_->get_joueur_courant() != couleur){
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

void Piece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if(echec_model_ && echec_model_->get_joueur_courant() != couleur){
        event->ignore();
        return;
    }
    QGraphicsObject::mouseReleaseEvent(event);
    setCursor(Qt::OpenHandCursor);
    QPointF scenePos = event->scenePos();
    int x = static_cast<int>(scenePos.x() / TAILLE_CASE_ECHIQUIER);
    int y = static_cast<int>(scenePos.y() / TAILLE_CASE_ECHIQUIER);
    if(position == Position(x, y)) {
        mise_a_jour_rendu();
        return;
    }
    emit piece_relache(x, y);
}

void Piece::mise_a_jour_rendu() {
    setPos(position.getX() * TAILLE_CASE_ECHIQUIER, position.getY() * TAILLE_CASE_ECHIQUIER);
    update();
}

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

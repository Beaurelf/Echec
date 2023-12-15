#include "echec_model.h"

EchecModel::EchecModel(bool machine, QObject* object) : QObject(object), machine_(machine)
{
    initialiser();
    joueur_courant_ = BLANC;
}

const Couleur& EchecModel::get_joueur_courant() const
{
    return joueur_courant_;
}

void EchecModel::initialiser()
{
    piece_selectionnee_ = nullptr;
    ancienne_piece_selectionnee_ = nullptr;
    // initialisation des pieces avec nullptr
    for (size_t i(0); i < pieces_.size(); ++i) {
        for (size_t j(0); j < pieces_[i].size(); ++j) {
            pieces_[i][j] = nullptr;
        }
    }

    //placement des pions
    for (size_t i(0); i < 8; ++i) {
        pieces_[1][i] = new Soldat(i, 1, NOIR, i, 1);
        pieces_[6][i] = new Soldat(i, 6, BLANC, i, 6);
    }

    pieces_[0][0] = new Tour(0, 0, NOIR);
    pieces_[0][7] = new Tour(7, 0, NOIR);

    pieces_[0][1] = new Chevalier(1, 0, NOIR);
    pieces_[0][6] = new Chevalier(6, 0, NOIR);

    pieces_[0][2] = new Fou(2, 0, NOIR);
    pieces_[0][5] = new Fou(5, 0, NOIR);

    pieces_[0][3] = new Reine(3, 0, NOIR);
    pieces_[0][4] = new Roi(4, 0, NOIR);
    roi_noir_ = pieces_[0][4];

    pieces_[7][0] = new Tour(0, 7, BLANC);
    pieces_[7][7] = new Tour(7, 7, BLANC);

    pieces_[7][1] = new Chevalier(1, 7, BLANC);
    pieces_[7][6] = new Chevalier(6, 7, BLANC);

    pieces_[7][2] = new Fou(2, 7, BLANC);
    pieces_[7][5] = new Fou(5, 7, BLANC);

    pieces_[7][3] = new Reine(3, 7, BLANC);
    pieces_[7][4] = new Roi(4, 7, BLANC);
    roi_blanc_ = pieces_[7][4];
}

std::array<std::array<Piece*, 8>, 8> EchecModel::get_pieces()
{
    return pieces_;
}

Piece* EchecModel::get_piece_selectionnee()
{
    return piece_selectionnee_;
}

Piece* EchecModel::get_ancienne_piece_selectionnee()
{
    return ancienne_piece_selectionnee_;
}

vector<Position> EchecModel::deplacement_possibles()
{
    return deplacement_possibles_;
}

vector<Position> EchecModel::ancien_deplacement_possibles()
{
    return ancienne_piece_selectionnee_->positions_possibles(pieces_);
}

void EchecModel::selectionner_piece(int i, int j)
{
    deplacement_possibles_.clear();
    if(piece_selectionnee_ == nullptr)
        piece_selectionnee_ = pieces_[i][j];
    else
    {
        ancienne_piece_selectionnee_ = piece_selectionnee_;
        piece_selectionnee_ = pieces_[i][j];
    }
    deplacement_possibles_ = piece_selectionnee_->positions_possibles(pieces_);
    emit piece_selectionee();
}

void EchecModel::set_promotion(const Type& type, int x, int y)
{
    switch (type) {
    case Type::CHEVALIER:
        piece_selectionnee_ = new Chevalier(x, y, joueur_courant_);
        break;
    case Type::REINE:
        piece_selectionnee_ = new Reine(x, y, joueur_courant_);
        break;
    case Type::FOU:
        piece_selectionnee_ = new Fou(x, y, joueur_courant_);
        break;
    case Type::TOUR:
        piece_selectionnee_ = new Tour(x, y, joueur_courant_);
        break;
    default:
        break;
    }
}

void EchecModel::deplacer_piece(int i, int j)
{
    // converser postion ou on peut manger pour enlever la couleur rouge dans la vue
    vector<Position> positions_mangeable;
    vector<Position> positions_non_mangeable;
    for_each(deplacement_possibles_.begin(), deplacement_possibles_.end(), [&](const Position& pos){
        if(piece_selectionnee_->peut_manger(pos, pieces_))
            positions_mangeable.push_back(pos);
        else
            positions_non_mangeable.push_back(pos);
    });
    pieces_[piece_selectionnee_->get_position().getY()][piece_selectionnee_->get_position().getX()] = nullptr;
    piece_selectionnee_->se_deplacer(j, i, pieces_);

    if(piece_selectionnee_->get_type() == SOLDAT)
    {
        if((piece_selectionnee_->get_y_init() == 1 and i == 7) or (piece_selectionnee_->get_y_init() == 6 and i == 0))
        {
            Position position_avant_promotion = piece_selectionnee_->get_ancienne_position();
            delete piece_selectionnee_;
            emit choix_promotion(i, j);
            emit piece_promue(position_avant_promotion);
        }
    }

    pieces_[i][j] = piece_selectionnee_;
    piece_selectionnee_ = nullptr;
    ancienne_piece_selectionnee_ = nullptr;
    joueur_courant_ = joueur_courant_ == BLANC ? NOIR : BLANC;
    emit piece_deplacee(i, j, positions_mangeable, positions_non_mangeable);
    if(est_en_echec())
    {
        emit roi_en_echec();
    }
}

void EchecModel::manger_piece(int i, int j)
{
    string image = pieces_[i][j]->get_image();
    delete pieces_[i][j];
    deplacer_piece(i, j);
    emit piece_mangee(image);
}

bool EchecModel::est_en_echec()
{
    Piece* roi = (joueur_courant_ == BLANC) ? roi_blanc_ : roi_noir_;
    for (size_t i(0); i < pieces_.size(); ++i) {
        for (size_t j(0); j < pieces_[i].size(); ++j) {
            if(pieces_[i][j] != nullptr && pieces_[i][j]->get_couleur() != joueur_courant_)
            {
                if(pieces_[i][j]->deplacement_valide(roi->get_position().getX(), roi->get_position().getY(), pieces_))
                    return true;
            }
        }
    }
    return false;
}

EchecModel::~EchecModel()
{
    roi_blanc_ = nullptr;
    roi_noir_ = nullptr;
    delete piece_selectionnee_;
    piece_selectionnee_ = nullptr;
    delete ancienne_piece_selectionnee_;
    ancienne_piece_selectionnee_ = nullptr;

    for (size_t i(0); i < pieces_.size(); ++i) {
        for (size_t j(0); j < pieces_[i].size(); ++j) {
            delete pieces_[i][j];
            pieces_[i][j] = nullptr;
        }
    }

}

#include "echec_model.h"
#include "algorithm"
#include "soldat.h"
#include "chevalier.h"
#include "fou.h"
#include "roi.h"
#include "reine.h"
#include "tour.h"


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

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            pieces_[Position(x, y)] = nullptr;
        }
    }

    // Placement des pions
    for (size_t i = 0; i < 8; ++i) {
        pieces_[Position(i, 1)] = new Soldat(i, 1, NOIR);
        pieces_[Position(i, 6)] = new Soldat(i, 6, BLANC);
    }

    // Tours
    pieces_[Position(0, 0)] = new Tour(0, 0, NOIR);
    pieces_[Position(7, 0)] = new Tour(7, 0, NOIR);
    pieces_[Position(0, 7)] = new Tour(0, 7, BLANC);
    pieces_[Position(7, 7)] = new Tour(7, 7, BLANC);

    // Cavaliers
    pieces_[Position(1, 0)] = new Chevalier(1, 0, NOIR);
    pieces_[Position(6, 0)] = new Chevalier(6, 0, NOIR);
    pieces_[Position(1, 7)] = new Chevalier(1, 7, BLANC);
    pieces_[Position(6, 7)] = new Chevalier(6, 7, BLANC);

    // Fous
    pieces_[Position(2, 0)] = new Fou(2, 0, NOIR);
    pieces_[Position(5, 0)] = new Fou(5, 0, NOIR);
    pieces_[Position(2, 7)] = new Fou(2, 7, BLANC);
    pieces_[Position(5, 7)] = new Fou(5, 7, BLANC);

    // Reines
    pieces_[Position(3, 0)] = new Reine(3, 0, NOIR);
    pieces_[Position(3, 7)] = new Reine(3, 7, BLANC);

    // Rois
    pieces_[Position(4, 0)] = new Roi(4, 0, NOIR);
    roi_noir_ = pieces_[Position(4, 0)];

    pieces_[Position(4, 7)] = new Roi(4, 7, BLANC);
    roi_blanc_ = pieces_[Position(4, 7)];
}

Pieces EchecModel::get_pieces() const {
    return pieces_;
}

Piece* EchecModel::get_piece(int i, int j)
{
    auto it = pieces_.find(Position(i, j));
    if(it == pieces_.end()) return nullptr;
    return it->second;
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

bool EchecModel::deplacement_met_en_echec(Piece* piece, const Position& pos)
{
    string cache_key = piece->get_position().to_string() + ">" + pos.to_string();

    // Vérifier le cache d'abord
    auto cache_it = echec_cache_.find(cache_key);
    if (cache_it != echec_cache_.end()) {
        return cache_it->second;
    }
    piece->se_deplacer(pos, pieces_);
    Piece* piece_pos = pieces_[pos];
    pieces_[pos] = piece; // on simule le deplacement de la piece
    bool resultat = est_en_echec();
    pieces_[pos] = piece_pos; // on reinitialise si c'etait un pointeur nul
    piece->retour_position();
    echec_cache_[cache_key] = resultat;
    return resultat;
}

void EchecModel::selectionner_piece(int i, int j)
{
    deplacement_possibles_.clear();
    if(piece_selectionnee_ != nullptr)
        ancienne_piece_selectionnee_ = piece_selectionnee_;
    piece_selectionnee_ = get_piece(i, j);
    // Vérifier si nous avons des mouvements en cache pour cette pièce
    Position pos = piece_selectionnee_->get_position();
    string cache_key = pos.to_string() + "_" + std::to_string(joueur_courant_ == BLANC ? 1 : 0);

    auto cache_it = positions_cache_.find(cache_key);
    if (cache_it != positions_cache_.end()) {
        deplacement_possibles_ = cache_it->second;
    }else{
        deplacement_possibles_ = piece_selectionnee_->positions_possibles(pieces_);
        // enlevement les deplacements mettant le roi en echec
        auto it = remove_if(deplacement_possibles_.begin(), deplacement_possibles_.end(), [&](const Position& pos){
            return deplacement_met_en_echec(piece_selectionnee_, pos);
        });
        deplacement_possibles_.erase(it, deplacement_possibles_.end());
        positions_cache_[cache_key] = deplacement_possibles_;
    }
    emit piece_selectionee();
}

void EchecModel::set_promotion(const Type& type, int x, int y)
{
    delete piece_selectionnee_;
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
    emit piece_promue(piece_selectionnee_);
}

void EchecModel::deplacer_piece(int i, int j)
{
    Position position(i, j);
    // vérifier si deplacement ne cause pas l'echec du roi
    auto it = find_if(deplacement_possibles_.begin(), deplacement_possibles_.end(), [&](const Position& pos){
        return pos == position;
    });

    if(it != deplacement_possibles_.end())
    {
        // S'il y'a une piece alors on la mange
        if(get_piece(i, j) != nullptr)
            manger_piece(i, j);
        // converser postion ou on pouvait se déplacer pour enlever les marqueurs dans la vue
        vector<Position> positions = deplacement_possibles_;
        pieces_[piece_selectionnee_->get_position()] = nullptr;
        piece_selectionnee_->se_deplacer(position, pieces_);

        if(auto soldat = dynamic_cast<Soldat*>(piece_selectionnee_))
        {
            if((soldat->get_y_init() == 1 && j == 7) || (soldat->get_y_init() == 6 && j == 0))
            {
                emit choix_promotion(i, j);
            }
        }

        delete pieces_[position];
        pieces_[position] = piece_selectionnee_;

        emit piece_deplacee(pieces_[position], positions);

        piece_selectionnee_ = nullptr;
        ancienne_piece_selectionnee_ = nullptr;
        positions_cache_.clear();
        echec_cache_.clear();
        joueur_courant_ = joueur_courant_ == BLANC ? NOIR : BLANC;
        if(est_en_echec())
        {
            if(echec_et_mat())
                emit roi_en_echec_et_mat();
            else
                emit roi_en_echec();
        }
    }
}

void EchecModel::manger_piece(int i, int j)
{
    emit piece_mangee(pieces_[Position(i, j)]);
}

bool EchecModel::est_en_echec() const
{
    Piece* roi = (joueur_courant_ == BLANC) ? roi_blanc_ : roi_noir_;
    for(auto& p : pieces_){
        if(p.second != nullptr && p.second->get_couleur() != joueur_courant_){
            if(p.second->deplacement_valide(roi->get_position(), pieces_)) return true;
        }
    }
    return false;
}

bool EchecModel::echec_et_mat()
{
    for(auto& p : pieces_){
        if(p.second != nullptr && p.second->get_couleur() != joueur_courant_){
            vector<Position> deplacement_possibles = p.second->positions_possibles(pieces_);
            for (const auto& deplacement : deplacement_possibles) {
                if (!deplacement_met_en_echec(p.second, deplacement))
                    return false;
            }
        }
    }
    return true;
}

EchecModel::~EchecModel()
{
    roi_blanc_ = nullptr;
    roi_noir_ = nullptr;
    piece_selectionnee_ = nullptr;
    ancienne_piece_selectionnee_ = nullptr;

    for (auto& p: pieces_) {
        delete p.second;
        p.second = nullptr;
    }

}

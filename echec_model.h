#ifndef ECHEC_MODEL_H
#define ECHEC_MODEL_H
#include "piece.h"
#include "soldat.h"
#include "chevalier.h"
#include "fou.h"
#include "roi.h"
#include "reine.h"
#include "tour.h"
#include "QDebug"
#include "algorithm"
#include "iterator"

#include <QObject>

class EchecModel : public QObject
{
    Q_OBJECT
public:
    EchecModel(bool machine, QObject* object = nullptr);
    ~EchecModel();
    void initialiser();
    array<std::array<Piece*, 8>, 8> get_pieces();
    bool est_en_echec(const Couleur& joueur); // si un des roi est en echec
    bool echec_et_mat() const;
    void selectionner_piece(int i, int j);
    void deplacer_piece(int i, int j);
    void manger_piece(int i, int j);
    Piece* get_piece_selectionnee();
    Piece* get_ancienne_piece_selectionnee();
    vector<Position> ancien_deplacement_possibles(); // renvoie les deplacements possibles de l ancienne piece selectionee
    vector<Position> deplacement_possibles(); // renvoie les deplacements possibles de la piece selectionee
    const Couleur& get_joueur_courant() const;
    bool est_en_echec();
    void set_promotion(const Type& type, int x, int y);

signals:
    void piece_selectionee();
    void piece_deplacee(int i, int j, vector<Position> positions_mangeable, vector<Position> positions_non_mangeable);
    void piece_promue(Position position_avant_promotion);
    void piece_mangee(string image);
    void roi_en_echec();
    void choix_promotion(int i, int j);

private:
    array<array<Piece*, 8>, 8> pieces_; // contient les pieces du joueur
    vector<Position> deplacement_possibles_;
    vector<Piece*> pieces_a_jouer_;
    Piece* piece_selectionnee_; // pointe vers une piece selectionnée
    Piece* ancienne_piece_selectionnee_; // pointe vers l'ancienne piece selectionnée
    Piece* roi_noir_;
    Piece* roi_blanc_;
    Couleur joueur_courant_;
    bool machine_;
};

#endif // ECHEC_MODEL_H

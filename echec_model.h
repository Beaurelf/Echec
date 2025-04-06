#ifndef _PIECE_
#define _PIECE_

#include <QObject>
#include <vector>
#include "utils.h"
#include "piece.h"

using namespace Utils;
using namespace std;

class EchecModel : public QObject
{
    Q_OBJECT
public:
    EchecModel(bool machine, QObject* object = nullptr);
    ~EchecModel();
    void initialiser();
    Piece* get_piece(int i, int j);
    Pieces get_pieces() const;
    void selectionner_piece(int i, int j);
    void deplacer_piece(int i, int j);
    void manger_piece(int i, int j);
    Piece* get_piece_selectionnee();
    Piece* get_ancienne_piece_selectionnee();
    vector<Position> ancien_deplacement_possibles(); // renvoie les deplacements possibles de l ancienne piece selectionee
    vector<Position> deplacement_possibles(); // renvoie les deplacements possibles de la piece selectionee
    const Couleur& get_joueur_courant() const;
    bool est_en_echec() const;
    bool echec_et_mat();
    void set_promotion(const Type& type, int x, int y);
    bool deplacement_met_en_echec(Piece* piece, const Position& position);

signals:
    void piece_selectionee();
    void piece_deplacee(std::vector<Position> positions);
    void piece_mangee(const Type& type);
    void roi_en_echec();
    void roi_en_echec_et_mat();
    void roi_echec_et_mat(Piece* piece);
    void choix_promotion(int i, int j);
    void piece_promue(Piece* piece);

private:
    Pieces pieces_; // contient les pieces du joueur
    vector<Position> deplacement_possibles_;
    Piece* piece_selectionnee_; // pointe vers une piece selectionnée
    Piece* ancienne_piece_selectionnee_; // pointe vers l'ancienne piece selectionnée
    Piece* roi_noir_;
    Piece* roi_blanc_;
    Couleur joueur_courant_;
    bool machine_;
    std::unordered_map<string, vector<Position>> positions_cache_;
    std::unordered_map<string, bool> echec_cache_;
};
#endif

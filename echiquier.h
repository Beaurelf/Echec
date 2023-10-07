#ifndef ECHIQUIER_H
#define ECHIQUIER_H

#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QIcon>
#include <QDebug>
#include <QLabel>
#include "piece.h"
#include "soldat.h"
#include "chevalier.h"
#include "fou.h"
#include "roi.h"
#include "reine.h"
#include "tour.h"

typedef std::array<std::array<QPushButton*,8>,8> Tabechiquier;

class Echiquier : public QWidget
{
    Q_OBJECT

private:
    Tabechiquier tabechiquier;
    std::array<std::array<Piece*, 8>, 8> pieces; // contient les pieces du joueur
    Piece* piece_selectionnee; // pointe vers une piece selectionnée
    Piece* ancienne_piece_selectionnee; // pointe vers l'ancienne piece selectionnée
    Couleur joueur_courant = BLANC;
    QLabel* label_joueur; // indiquant quel joueur doit jouer
    bool machine; // true si le joueur joue contre la machine

public:
    Echiquier(bool machine, QMainWindow *parent = nullptr);
    ~Echiquier();
    void initialiser();

public slots:
    void afficher_deplacement_possibles(int i, int j);
    void deplacer(int i, int j);

};

#endif // ECHIQUIER_H

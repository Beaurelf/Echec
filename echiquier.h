#ifndef ECHIQUIER_H
#define ECHIQUIER_H

#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QIcon>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QDialog>
#include <QRadioButton>

#include "echec_model.h"

typedef array<array<QPushButton*,8>,8> Tabechiquier;

class Echiquier : public QWidget
{
    Q_OBJECT

private:
    Tabechiquier tabechiquier;
    QLabel* label_joueur; // indiquant quel joueur doit jouer
    bool machine; // true si le joueur joue contre la machine
    EchecModel* echec_model_;

public:
    Echiquier(bool machine, QMainWindow *parent = nullptr);
    ~Echiquier();
    void setup();

public slots:
    void case_pressee(int i, int j);
    void afficher_deplacement_possibles();
    void deplacer_piece(int i, int j, vector<Position> positions_mangeable, vector<Position> positions_non_mangeable);
    void roi_en_echec();
    void choix_promotion(int i, int j);
    void piece_promue(Position position_avant_promotion);
    //void piece_mangee(string image);

};

#endif // ECHIQUIER_H

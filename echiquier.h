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
#include <QGraphicsScene>
#include <QGraphicsView>
#include "case_echequier.h"
#include "echec_model.h"

typedef array<array<CaseEchequier*, TAILLE_ECHIQUIER>, TAILLE_ECHIQUIER> Tabechiquier;

class Echiquier : public QWidget
{
    Q_OBJECT

private:
    QGraphicsScene* scene_;
    QGraphicsView* view_;
    Tabechiquier tabechiquier_;
    QLabel* label_joueur_; // indiquant quel joueur doit jouer
    QMainWindow *parent_;
    bool machine_; // true si le joueur joue contre la machine
    EchecModel* echec_model_;
    QVBoxLayout* pieces_noires_mangees_;
    QVBoxLayout* pieces_blanches_mangees_;
    vector<QLabel*> pieces_noires_capturees_;
    vector<QLabel*> pieces_blanches_capturees_;
public:
    Echiquier(bool machine, QMainWindow *parent = nullptr);
    ~Echiquier();
    void setupUi();
    void setup();
    void update_nbre_pieces_capturees(int index);

signals:
    void  recommencer();
    void aller_accueil();

public slots:
    void case_pressee(int i, int j);
    void afficher_deplacement_possibles();
    void deplacer_piece(vector<Position> positions);
    void roi_en_echec();
    void choix_promotion(int i, int j);
    void piece_mangee(const Type& type);
    void roi_en_echec_et_mat();
};

#endif // ECHIQUIER_H

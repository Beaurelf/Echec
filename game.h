#ifndef GAME_H
#define GAME_H
#include "home.h"
#include "echiquier.h"
#include <QMainWindow>
#include <QWidget>

class Game : public QMainWindow
{
    Q_OBJECT
private:
    Home* home_;
    Echiquier* echiquier_;
    QWidget* conteneur_;
    QHBoxLayout* layout_;
    QPushButton* btn_recommencer_;
    QPushButton* btn_accueil_;
    bool machine_;

public:
    Game(QWidget *parent = nullptr);
    ~Game();
    void setup();

public slots:
    void accueil();
    void lancer_jeu(bool machine);
    void recommencer();
    void quitter_jeu();
};
#endif // GAME_H

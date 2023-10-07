#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QGraphicsEffect>
#include <QPushButton>
#include "echiquier.h"


class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QMainWindow* parent = nullptr);
    ~Home();

public slots:
    void lancer_jeu(bool machine, QMainWindow* window);
    void quitter_jeu(QMainWindow* window);
};
#endif // HOME_H
